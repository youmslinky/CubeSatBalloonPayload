/*
 * ultimate_gps_driver.c
 *
 * Created: 2/15/2018 7:32:20 PM
 *  Author: jdk0026
 */ 


 #include "drivers/usart_driver.h"

/*
format of packets is comma delimited fields
example:	$GPRMC,194509.000,	A,							4042.6142,				N,07400.4168,W,2.03,221.11,160412,,,A*77
format:			   HHMMSS.SSS	C							DDMM.MMMM,				 ,DDDMM.MMMM, ,S.SS,HHH.HH,
notes:	   GMT					validty: (A)ctive,(V)oid	lat: degrees,minutes	

*/
	