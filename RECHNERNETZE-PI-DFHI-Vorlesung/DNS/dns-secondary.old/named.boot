; created by fje@rz.uni-sb.de 14.9.94
;
;
;  boot file for secondary nameserver
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
;	secondary zones for htw
;
secondary	htw.uni-sb.de.		  134.96.160.103 	    	htw
secondary	htw-saarland.de.	  134.96.160.103 	    	saarland
;
primary		0.0.127.in-addr.arpa			named.local
secondary    	156.96.134.in-addr.arpa   134.96.160.103              rev.156
secondary    	157.96.134.in-addr.arpa   134.96.160.103              rev.157
secondary    	158.96.134.in-addr.arpa   134.96.160.103              rev.158
secondary    	159.96.134.in-addr.arpa   134.96.160.103              rev.159
secondary    	160.96.134.in-addr.arpa   134.96.160.103              rev.160
secondary    	161.96.134.in-addr.arpa   134.96.160.103              rev.161
;
;
;
;py von pauly ausgeixt 22.02.1996
;include primaries
;include secondaries
