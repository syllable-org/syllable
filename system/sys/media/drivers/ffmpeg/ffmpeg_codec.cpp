/*  FFMPEG Codec plugin
 *  Copyright (C) 2003 Arno Klenke
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of version 2 of the GNU Library
 *  General Public License as published by the Free Software
 *  Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 *  MA 02111-1307, USA
 */

#include <media/codec.h>
#include <iostream>

#define FFMPEG_CACHE_SIZE 256 * 1024

extern "C"
{
	#include "avformat.h"
	#include "avcodec.h"
}

class FFMpegCodec : public os::MediaCodec
{
public:
	FFMpegCodec();
	~FFMpegCodec();
	
	os::String 		GetIdentifier();
	os::View*		GetConfigurationView();
	
	status_t 		Open( os::MediaFormat_s sFormat, os::MediaFormat_s sExternal, bool bEncode );
	void 			Close();
	
	os::MediaFormat_s GetInternalFormat();
	os::MediaFormat_s GetExternalFormat();
	
	status_t 		CreateAudioOutputPacket( os::MediaPacket_s* psOutput );
	void			DeleteAudioOutputPacket( os::MediaPacket_s* psOutput );
	
	status_t		CreateVideoOutputPacket( os::MediaPacket_s* psOutput );
	void			DeleteVideoOutputPacket( os::MediaPacket_s* psOutput );
	
	status_t		DecodePacket( os::MediaPacket_s* psPacket, os::MediaPacket_s* psOutput );
	status_t		EncodePacket( os::MediaPacket_s* psPacket, os::MediaPacket_s* psOutput );
private:
	uint32			Resample( uint16* pDst, uint16* pSrc, uint32 nLength );
	bool			m_bEncode;
	AVStream		m_sDecodeStream;
	AVCodecContext	m_sDecodeContext;
	AVStream  		m_sEncodeStream;
	os::MediaFormat_s m_sInternalFormat;
	os::MediaFormat_s m_sExternalFormat;
	uint8*			m_pCache;
	uint32			m_nCachePointer;
	bool			m_bEncodeResample;
};

FFMpegCodec::FFMpegCodec()
{
	/* Create encoding cache */
	m_pCache = ( uint8* )malloc( FFMPEG_CACHE_SIZE );
	memset( m_pCache, 0, FFMPEG_CACHE_SIZE );
}

FFMpegCodec::~FFMpegCodec()
{
	free( m_pCache );
}

os::String FFMpegCodec::GetIdentifier()
{
	return( "FFMpeg Codec" );
}


os::View* FFMpegCodec::GetConfigurationView()
{
	return( NULL );
}

status_t FFMpegCodec::Open( os::MediaFormat_s sFormat, os::MediaFormat_s sExternal, bool bEncode )
{
	CodecID id;
	AVCodec* psCodec;
	
	if( bEncode )
		psCodec = avcodec_find_encoder_by_name( sFormat.zName.c_str() );
	else
		psCodec = avcodec_find_decoder_by_name( sFormat.zName.c_str() );
	
	if( psCodec == NULL )
		return( -1 );
		
	id = psCodec->id;

	if( sExternal.zName.str() != "Raw Audio" && sExternal.zName.str() != "Raw Video" )
		return( -1 );
		
	if( !bEncode )
	{
		if( sFormat.pPrivate == NULL ) {
			std::cout<<"The FFMpeg codec does only work together with the FFMpeg input"<<std::endl;
			return( -1 );
		}
		/* Check decoding parameters */
		if( sExternal.nSampleRate !=0 || sExternal.nChannels != 0
		|| sExternal.nWidth != 0 || sExternal.nHeight != 0 ) {
			std::cout<<"Format conversion not supported by the FFMpeg codec"<<std::endl;
			return( -1 );
		}
	} else
	{
		/* Check encoding parameters */
		if( sFormat.nSampleRate !=0 || sFormat.nChannels != 0
		|| sFormat.nWidth != 0 || sFormat.nHeight != 0 ) {
			std::cout<<"Format conversion not supported by the FFMpeg codec"<<std::endl;
			return( -1 );
		}
	}
		
	MEDIA_CLEAR_FORMAT( m_sInternalFormat );
	MEDIA_CLEAR_FORMAT( m_sExternalFormat );
	m_bEncode = bEncode;
	
	m_sInternalFormat = sFormat;
	m_sInternalFormat.pPrivate = NULL;
	m_sExternalFormat = sExternal;
	m_sExternalFormat.bVFR = m_sInternalFormat.bVFR;
	
	
	
	/* Set decoding parameters */
	
	if( !m_bEncode ) 
	{
		m_sDecodeStream = *( ( AVStream* )(sFormat.pPrivate) );
		m_sDecodeContext = m_sDecodeStream.codec;
	
		AVCodec *psCodec = avcodec_find_decoder( id );
	
		if( id == CODEC_ID_MPEG1VIDEO )
			m_sDecodeContext.flags |= CODEC_FLAG_TRUNCATED;
		if( psCodec == NULL || avcodec_open( &m_sDecodeContext, psCodec ) < 0 )
		{
			std::cout<<"Error while opening codec "<<sFormat.zName.c_str()<<std::endl;
			return( -1 );
		}
	}
		
	/* Set encoding parameters */
	if( m_bEncode && sFormat.nType == os::MEDIA_TYPE_AUDIO ) 
	{
		/* Prepare stream for the ffmpeg output */
		m_sEncodeStream.start_time = AV_NOPTS_VALUE;
		m_sEncodeStream.duration = AV_NOPTS_VALUE;
		m_sEncodeStream.cur_dts = AV_NOPTS_VALUE;
		av_set_pts_info( &m_sEncodeStream, 33, 1, 90000 );
	    m_sEncodeStream.last_IP_pts = AV_NOPTS_VALUE;
		
		AVCodecContext *sEnc = &m_sEncodeStream.codec;
		memset( sEnc, 0, sizeof( AVCodecContext ) );
		avcodec_get_context_defaults( &m_sEncodeStream.codec );
		sEnc->codec_type = CODEC_TYPE_AUDIO;
		sEnc->codec_id = id;
		
		
		if( sFormat.nBitRate == 0 )
			sEnc->bit_rate = sExternal.nBitRate;
		else
			sEnc->bit_rate = sFormat.nBitRate;
		sEnc->sample_rate = sExternal.nSampleRate;
		sEnc->strict_std_compliance = 1;
		sEnc->thread_count = 1;
		
		/* Always do channel conversion for now */
		
		if( sExternal.nChannels > 2 ) {
			sEnc->channels = 2;
			m_bEncodeResample = true;
		}
		else {
			sEnc->channels = sExternal.nChannels;
			m_bEncodeResample = false;
		}

		/* Open encoder */
	
		AVCodec *psEncCodec = avcodec_find_encoder( sEnc->codec_id );
		if( psEncCodec ) {
			if( avcodec_open( sEnc, psEncCodec ) >= 0 ) {
				m_sInternalFormat.pPrivate = &m_sEncodeStream;
			}
		}
	}
	
	if( m_bEncode && sFormat.nType == os::MEDIA_TYPE_VIDEO )
	{
		/* Prepare stream for the ffmpeg output */
		m_sEncodeStream.start_time = AV_NOPTS_VALUE;
		m_sEncodeStream.duration = AV_NOPTS_VALUE;
		m_sEncodeStream.cur_dts = AV_NOPTS_VALUE;
		av_set_pts_info( &m_sEncodeStream, 33, 1, 90000 );
	    m_sEncodeStream.last_IP_pts = AV_NOPTS_VALUE;
		
		AVCodecContext *sEnc = &m_sEncodeStream.codec;
		memset( sEnc, 0, sizeof( AVCodecContext ) );
		avcodec_get_context_defaults( &m_sEncodeStream.codec );
		sEnc->codec_type = CODEC_TYPE_VIDEO;
		sEnc->codec_id = id;
		if( sFormat.nBitRate == 0 )
			sEnc->bit_rate = sExternal.nBitRate;
		else
			sEnc->bit_rate = sFormat.nBitRate;
			
		sEnc->bit_rate_tolerance = 400*1000;
		
		/* No variable framerates supported for now */
		#if 0
		if( sExternal.bVFR ) {
			std::cout<<"Cannot encode video with variable framerate!"<<std::endl;
			return( -1 );
		}
		#endif
		m_sEncodeStream.r_frame_rate.num = (int)sExternal.vFrameRate;
		m_sEncodeStream.r_frame_rate.den = 1;
		sEnc->time_base.den = (int)sExternal.vFrameRate;
		sEnc->time_base.num = 1;
		sEnc->width = sExternal.nWidth;
		sEnc->height = sExternal.nHeight;
//		sEnc->aspect_ratio = sExternal.nWidth / sExternal.nHeight;
		sEnc->pix_fmt = PIX_FMT_YUV420P;
	
		sEnc->gop_size = 12;
		sEnc->qmin = 2;
		sEnc->qmax = 31;
		sEnc->mb_qmin = 2;
		sEnc->mb_qmax = 31;
		sEnc->max_qdiff = 3;
		sEnc->qblur = 0.5;
		sEnc->qcompress = 0.5;
		sEnc->rc_eq = "tex^qComp";
		sEnc->debug = 0;
		sEnc->rc_override_count = 0;
		sEnc->rc_max_rate = 0;
		sEnc->rc_min_rate = 0;
		sEnc->rc_buffer_size = 0;
		sEnc->rc_buffer_aggressivity = 1.0;
		sEnc->rc_initial_cplx = 0;
		sEnc->i_quant_factor = -0.8;
		sEnc->b_quant_factor = 1.25;
		sEnc->i_quant_offset = 0.0;
		sEnc->b_quant_offset = 1.25;
		sEnc->dct_algo = 0;
		sEnc->idct_algo = 0;
		sEnc->strict_std_compliance = 0;
		sEnc->me_method = ME_EPZS;
	
		/* Open encoder */
		AVCodec *psEncCodec = avcodec_find_encoder( sEnc->codec_id );
		if( psEncCodec ) {
			if( avcodec_open( sEnc, psEncCodec ) >= 0 ) {
				m_sInternalFormat.pPrivate = &m_sEncodeStream;
			} else {
				return( -1 );
			}
		} else {
			return( -1 );
		}
	}
	m_nCachePointer = 0;
	
	return( 0 );
}

void FFMpegCodec::Close()
{
	if( !m_bEncode )
		avcodec_close( &m_sDecodeContext );
	else
		avcodec_close( &m_sEncodeStream.codec );
}

os::MediaFormat_s FFMpegCodec::GetInternalFormat()
{
	os::MediaFormat_s sFormat = m_sInternalFormat;
	if( !m_bEncode )
	{
		if( m_sDecodeContext.pix_fmt == PIX_FMT_YUV422 )
			sFormat.eColorSpace = os::CS_YUV422;
		else if( m_sDecodeContext.pix_fmt == PIX_FMT_YUV411P )
			sFormat.eColorSpace = os::CS_YUV411;
		else if( m_sDecodeContext.pix_fmt == PIX_FMT_YUV420P )
			sFormat.eColorSpace = os::CS_YUV12;
		else if( m_sDecodeContext.pix_fmt == PIX_FMT_YUV422P )
			sFormat.eColorSpace = os::CS_YUV422;
		else if( m_sDecodeContext.pix_fmt == PIX_FMT_RGB24 )
			sFormat.eColorSpace = os::CS_RGB24;
			
	} else {
		AVCodecContext *sEnc = &m_sEncodeStream.codec;
		sFormat.eColorSpace = os::CS_YUV12;
		sFormat.nSampleRate = sEnc->sample_rate;
		sFormat.nChannels = sEnc->channels;
		sFormat.vFrameRate = m_sEncodeStream.r_frame_rate.num;
		sFormat.nWidth = sEnc->width;
		sFormat.nHeight = sEnc->height;
	}
	
	return( sFormat );		
}

os::MediaFormat_s FFMpegCodec::GetExternalFormat()
{
	os::MediaFormat_s sFormat = m_sExternalFormat;
	if( !m_bEncode )
	{
		if( m_sDecodeContext.pix_fmt == PIX_FMT_YUV422 )
			sFormat.eColorSpace = os::CS_YUV422;
		else if( m_sDecodeContext.pix_fmt == PIX_FMT_YUV411P )
			sFormat.eColorSpace = os::CS_YUV411;
		else if( m_sDecodeContext.pix_fmt == PIX_FMT_YUV420P )
			sFormat.eColorSpace = os::CS_YUV12;
		else if( m_sDecodeContext.pix_fmt == PIX_FMT_YUV422P )
			sFormat.eColorSpace = os::CS_YUV422;
		else if( m_sDecodeContext.pix_fmt == PIX_FMT_RGB24 )
			sFormat.eColorSpace = os::CS_RGB24;
			
		sFormat.nSampleRate = m_sDecodeContext.sample_rate;
		sFormat.nChannels = m_sDecodeContext.channels;
		sFormat.vFrameRate = (float)m_sDecodeStream.r_frame_rate.num / (float)m_sDecodeStream.r_frame_rate.den;
		sFormat.nWidth = m_sDecodeContext.width;
		sFormat.nHeight = m_sDecodeContext.height;
	} else {
		sFormat.eColorSpace = os::CS_YUV12;
	}
	
	
	return( sFormat );		
}

status_t FFMpegCodec::CreateAudioOutputPacket( os::MediaPacket_s* psOutput )
{
	psOutput->pBuffer[0] = ( uint8* )malloc( 4 * AVCODEC_MAX_AUDIO_FRAME_SIZE );
	if(	psOutput->pBuffer[0] == NULL )
		return( -1 );
	return( 0 );
}


void FFMpegCodec::DeleteAudioOutputPacket( os::MediaPacket_s* psOutput )
{
	if( psOutput->pBuffer[0] != NULL )
		free( psOutput->pBuffer[0] );
}


status_t FFMpegCodec::CreateVideoOutputPacket( os::MediaPacket_s* psOutput )
{
	if( !m_bEncode )
		return( 0 );
	AVCodecContext *sEnc = &m_sEncodeStream.codec;
	psOutput->pBuffer[0] = ( uint8* )malloc( sEnc->width * sEnc->height * 4 );
	if(	psOutput->pBuffer[0] == NULL )
			return( -1 );
	return( 0 );
}


void FFMpegCodec::DeleteVideoOutputPacket( os::MediaPacket_s* psOutput )
{
	if( !m_bEncode )
		return;
	if( psOutput->pBuffer[0] != NULL )
		free( psOutput->pBuffer[0] );
}


status_t FFMpegCodec::DecodePacket( os::MediaPacket_s* psPacket, os::MediaPacket_s* psOutput )
{
	if( m_sInternalFormat.nType == os::MEDIA_TYPE_AUDIO )
	{
		int nSize = psPacket->nSize[0];
		uint8* pInput = psPacket->pBuffer[0];
		uint8* pOut = psOutput->pBuffer[0];
		int nOutSize = 0;
		psOutput->nSize[0] = 0;
	
		while( nSize > 0 ) {
			
			int nLen = avcodec_decode_audio( &m_sDecodeContext, (short *)pOut, &nOutSize, 
        	                              pInput, nSize);
			if( nLen < 0 ) {
				return( -1 );
			}
			if( nOutSize <= 0 ) {
			} else {
				psOutput->nSize[0] += nOutSize;
				pOut += nOutSize;
			}
			nSize -= nLen;
			pInput += nLen;
		}
		
		if( psOutput->nSize[0] > 0 )
			psOutput->nTimeStamp = psPacket->nTimeStamp;
	} 
	else 
	{
		int nSize = psPacket->nSize[0];
		uint8* pInput = psPacket->pBuffer[0];
		int bDecoded;
		AVFrame sFrame;
		psOutput->nSize[0] = 0;
	
		while( nSize > 0 ) {
			int nLen = avcodec_decode_video( &m_sDecodeContext, &sFrame, &bDecoded, 
   	                                   pInput, nSize );                      
			if( bDecoded > 0 ) {
				//std::cout<<"DECODED "<<psPacket->nTimeStamp<<std::endl;
				psOutput->nTimeStamp = psPacket->nTimeStamp;
				for( int i = 0; i < 4; i++ ) {
					psOutput->pBuffer[i] = sFrame.data[i];
					psOutput->nSize[i] = sFrame.linesize[i];
				}
			} else {
				//std::cout<<"NOT DECODED "<<psPacket->nTimeStamp<<std::endl;
			}
			if( nLen < 0 ) {
				return( -1 );
			}
			
			nSize -= nLen;
			pInput += nLen;
		}
	}
	return( 0 );
}


struct ffmpeg_frame
{
	uint32 nSize;
	ffmpeg_frame* pNext;
};


uint32 FFMpegCodec::Resample( uint16* pDst, uint16* pSrc, uint32 nLength )
{
	uint32 nSkipBefore = 0;
	uint32 nSkipBehind = 0;
	/* Calculate skipping ( I just guess what is right here ) */
	if( m_sExternalFormat.nChannels == 3 ) {
		nSkipBefore = 0;
		nSkipBehind = 1;
	} else if( m_sExternalFormat.nChannels == 4 ) {
		nSkipBefore = 2;
		nSkipBehind = 0;
	} else if( m_sExternalFormat.nChannels == 5 ) {
		nSkipBefore = 2;
		nSkipBehind = 1;
	} else if( m_sExternalFormat.nChannels == 6 ) {
		nSkipBefore = 2;
		nSkipBehind = 2;
	} 
	
	
	//cout<<"Resample"<<endl;
	for( uint32 i = 0; i < nLength / m_sExternalFormat.nChannels / 2; i++ ) 
	{
		/* Skip */
		pSrc += nSkipBefore;
		
		/* Channel 1 */
		*pDst++ = *pSrc++;
		
		/* Channel 2 */
		*pDst++ = *pSrc++;
		
		/* Skip */
		pSrc += nSkipBehind;
	}
	return( nLength * 2 / m_sExternalFormat.nChannels );
}

status_t FFMpegCodec::EncodePacket( os::MediaPacket_s* psPacket, os::MediaPacket_s* psOutput )
{
	psOutput->nTimeStamp = psPacket->nTimeStamp;
	
	if( m_sExternalFormat.nType == os::MEDIA_TYPE_AUDIO )
	{
		int nSize = psPacket->nSize[0];
		uint8* pOut = psOutput->pBuffer[0];
		psOutput->nSize[0] = 0;
		AVCodecContext *sEnc = &m_sEncodeStream.codec;
	
		//std::cout<<m_sEncodeStream.pts.num<<" "<<m_sEncodeStream.pts.den<<std::endl;
	
		if( sEnc->frame_size == 1 ) {
			switch( m_sEncodeStream.codec.codec_id ) {
				case CODEC_ID_PCM_S16LE:
				case CODEC_ID_PCM_S16BE:
				case CODEC_ID_PCM_U16LE:
				case CODEC_ID_PCM_U16BE:
				break;
				default:
					nSize = nSize >> 1;
				break;
			}
			
			m_nCachePointer = 0;
			if( !m_bEncodeResample ) {
				memcpy( m_pCache, psPacket->pBuffer[0], psPacket->nSize[0] );
				m_nCachePointer += nSize;
			} else {
				
				m_nCachePointer += Resample( (uint16*)m_pCache, (uint16*)psPacket->pBuffer[0], psPacket->nSize[0] );
				m_nCachePointer /= psPacket->nSize[0] / nSize;
			}
			
			
	    	psOutput->nSize[0] = avcodec_encode_audio( &m_sEncodeStream.codec, pOut, m_nCachePointer, ( const short* )m_pCache );
    		ffmpeg_frame* psFrame = ( ffmpeg_frame* )malloc( sizeof( ffmpeg_frame ) );
			psFrame->nSize = psOutput->nSize[0];
			psFrame->pNext = NULL;
			psOutput->pPrivate = psFrame;
    		return( 0 );
    	}
	
		/* Put packet into cache first */
		if( ( m_nCachePointer + psPacket->nSize[0] ) > FFMPEG_CACHE_SIZE ) {
			std::cout<<"Cache overflow!"<<std::endl;
			return( -1 );
		}
	
		if( !m_bEncodeResample ) {
			memcpy( m_pCache + m_nCachePointer, psPacket->pBuffer[0], psPacket->nSize[0] );
			m_nCachePointer += psPacket->nSize[0];
		} else {
			m_nCachePointer += Resample( (uint16*)m_pCache + m_nCachePointer / 2, (uint16*)psPacket->pBuffer[0], psPacket->nSize[0] );
		}
		//cout<<"Cache :"<<->nSize[0]<<endl;
	
		ffmpeg_frame* psFrames = NULL;
	
	start:
		uint32 nFrameBytes = (uint32)sEnc->frame_size * sEnc->channels * 2;
		/* Look if we have enough data for one frame */
		if( nFrameBytes < m_nCachePointer ) 
		{
			/* Note: We have to tell the ffmpeg output how we have split the packets */
			//cout<<"Encode :"<<nFrameBytes<<endl;
			int nLen = avcodec_encode_audio( &m_sEncodeStream.codec, pOut, 4 * AVCODEC_MAX_AUDIO_FRAME_SIZE, ( const short* )m_pCache );
			psOutput->nSize[0] += nLen;
			memcpy( m_pCache, m_pCache + nFrameBytes, m_nCachePointer - nFrameBytes );
			m_nCachePointer -= nFrameBytes;
			pOut += nLen;
			ffmpeg_frame* psFrame = ( ffmpeg_frame* )malloc( sizeof( ffmpeg_frame ) );
			psFrame->nSize = nLen;
			psFrame->pNext = psFrames;
			psFrames = psFrame;
			goto start;
		}
		psOutput->pPrivate = psFrames;
		return( 0 );	
	} else {
		/* Encode frame */
		AVFrame sFrame;
		avcodec_get_frame_defaults( &sFrame );
		for( int i = 0; i < 4; i++ ) {
			sFrame.data[i] = psPacket->pBuffer[i];
			sFrame.linesize[i] = psPacket->nSize[i]; 
		}
		sFrame.quality = m_sEncodeStream.quality;
		AVCodecContext *sEnc = &m_sEncodeStream.codec;
		psOutput->nSize[0] = avcodec_encode_video( &m_sEncodeStream.codec, psOutput->pBuffer[0], psPacket->nSize[0] * sEnc->height, &sFrame );
		
		if( psOutput->nSize[0] < 0 )
			return( -1 );
		return( 0 );
	}
}

os::MediaCodec* init_ffmpeg_codec()
{
	return( new FFMpegCodec() );
}

