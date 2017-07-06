; created by fje@rz.uni-sb.de 14.9.94
; letzte erweiterung durch wpy@htw.uni-sb.de 10.10.98
;
;
;  boot file for primary nameserver
;
; type     domain                  source file or host
;
; --- domain name served by this name server: htw.uni-sb.de and n-addr.arpa
;xfer-log   /var/log/named.log
;
;
directory  /etc/named.files
;
;
; --- file to hold cached IN addresses
cache      .    named.ca
forwarders	134.96.100.105 134.96.7.7 134.96.7.254 193.196.32.1
;
;	primary zones for htw

primary	   	htw.uni-sb.de		   	    	htw
primary	   	htw-saarland.de		   	    	saarland
;
primary		0.0.127.in-addr.arpa			named.local
primary    	156.96.134.in-addr.arpa                 rev.156
primary    	157.96.134.in-addr.arpa                 rev.157
primary    	158.96.134.in-addr.arpa                 rev.158
primary    	159.96.134.in-addr.arpa                 rev.159
primary    	160.96.134.in-addr.arpa                 rev.160
primary    	161.96.134.in-addr.arpa                 rev.161


;von pauly ausgeixt sun in.named kann das nicht !!!
;include primaries
;include secondaries
