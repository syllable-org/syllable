# Generate security keys for the OpenSSH server:

# Legacy RSA1 key for version 1 of the SSH protocol:
#if [ ! -f /etc/ssh/ssh_host_key ]
#then
#	/system/indexes/programs/ssh-keygen -t rsa1 -b 1024 -f /etc/ssh/ssh_host_key -N ''
#	chmod 600 /etc/ssh/ssh_host_key
#fi

if [ ! -f /etc/ssh/ssh_host_dsa_key ]
then
	/system/indexes/programs/ssh-keygen -d -f /etc/ssh/ssh_host_dsa_key -N ''
	chmod 600 /etc/ssh/ssh_host_dsa_key
fi
if [ ! -f /etc/ssh/ssh_host_rsa_key ]
then
	/system/indexes/programs/ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key -N ''
	chmod 600 /etc/ssh/ssh_host_rsa_key
fi


# Stop the server with:
#killall sshd
