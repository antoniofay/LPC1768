/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    HTTP_CGI.c
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013-12.05
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <adc.h>
#include <iap.h>
#include <timer.h>

/* ---------------------------------------------------------------------------
 * The HTTP server provides a small scripting language.
 *
 * The script language is simple and works as follows. Each script line starts
 * with a command character, either "i", "t", "c", "#" or ".".
 *   "i" - command tells the script interpreter to "include" a file from the
 *         virtual file system and output it to the web browser.
 *   "t" - command should be followed by a line of text that is to be output
 *         to the browser.
 *   "c" - command is used to call one of the C functions from the this file.
 *         It may be followed by the line of text. This text is passed to
 *         'cgi_func()' as a pointer to environment variable.
 *   "#' - command is a comment line and is ignored (the "#" denotes a comment)
 *   "." - denotes the last script line.
 *
 * --------------------------------------------------------------------------*/

/* http_demo.c */

/* at_System.c */
extern  LOCALM nlocalm[3];

/* Net_Config.c */
extern struct tcp_cfg   tcp_config;
extern struct http_cfg  http_config;
extern struct RemotePeer {
	uint8_t	 IP[4];
	uint16_t Port;
} Server, Admin;
extern struct RemotePeer Outdoor;
extern char	version[10];
extern uint8_t ComState;
#define tcp_NumSocks    tcp_config.NumSocks
#define tcp_socket      tcp_config.Scb
#define http_EnAuth     http_config.EnAuth
#define http_auth_passw http_config.Passw

/*----------------------------------------------------------------------------
 * HTTP Server Common Gateway Interface Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- cgi_process_var -------------------------------*/

void cgi_process_var (U8 *qs) {
  /* This function is called by HTTP server to process the Querry_String   */
  /* for the CGI Form GET method. It is called on SUBMIT from the browser. */
  /*.The Querry_String.is SPACE terminated.                                */
  U8 *var;
  int s[4];

  var = (U8 *)alloc_mem (40);
  do {
    /* Loop through all the parameters. */
    qs = http_get_var (qs, var, 40);
    /* Check the returned string, 'qs' now points to the next. */
    if (var[0] != 0) {
      /* Returned string is non 0-length. */
      if (str_scomp (var, "ip=") == __TRUE) {
        /* My IP address parameter. */
        sscanf ((const char *)&var[3], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        nlocalm[0].IpAdr[0]   = s[0];
        nlocalm[0].IpAdr[1]   = s[1];
        nlocalm[0].IpAdr[2]   = s[2];
        nlocalm[0].IpAdr[3]   = s[3];
      }
      else if (str_scomp (var, "msk=") == __TRUE) {
        /* Net mask parameter. */
        sscanf ((const char *)&var[4], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        nlocalm[0].NetMask[0] = s[0];
        nlocalm[0].NetMask[1] = s[1];
        nlocalm[0].NetMask[2] = s[2];
        nlocalm[0].NetMask[3] = s[3];
      }
      else if (str_scomp (var, "gw=") == __TRUE) {
        /* Default gateway parameter. */
        sscanf ((const char *)&var[3], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        nlocalm[0].DefGW[0]   = s[0];
        nlocalm[0].DefGW[1]   = s[1];
        nlocalm[0].DefGW[2]   = s[2];
        nlocalm[0].DefGW[3]   = s[3];
      }
      else if (str_scomp (var, "pdns=") == __TRUE) {
        /* Default gateway parameter. */
        sscanf ((const char *)&var[5], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        nlocalm[0].PriDNS[0]  = s[0];
        nlocalm[0].PriDNS[1]  = s[1];
        nlocalm[0].PriDNS[2]  = s[2];
        nlocalm[0].PriDNS[3]  = s[3];
      }
      else if (str_scomp (var, "sdns=") == __TRUE) {
        /* Default gateway parameter. */
        sscanf ((const char *)&var[5], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        nlocalm[0].SecDNS[0]  = s[0];
        nlocalm[0].SecDNS[1]  = s[1];
        nlocalm[0].SecDNS[2]  = s[2];
        nlocalm[0].SecDNS[3]  = s[3];
      }
			else if (str_scomp (var, "sip=") == __TRUE) {
        /* Server IP parameter. */
        sscanf ((const char *)&var[4], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        Server.IP[0] = s[0];
        Server.IP[1] = s[1];
				Server.IP[2] = s[2];
				Server.IP[3] = s[3];
      }
			else if (str_scomp (var, "aip=") == __TRUE) {
        /* Administrator IP parameter. */
        sscanf ((const char *)&var[4], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        Admin.IP[0] = s[0];
        Admin.IP[1] = s[1];
				Admin.IP[2] = s[2];
				Admin.IP[3] = s[3];
      }
			else if (str_scomp (var, "oip=") == __TRUE) {
        /* Outdoor unit IP parameter. */
        sscanf ((const char *)&var[4], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        Outdoor.IP[0] = s[0];
        Outdoor.IP[1] = s[1];
				Outdoor.IP[2] = s[2];
				Outdoor.IP[3] = s[3];
      }
			else if (str_scomp (var, "room") == __TRUE) {
				switch (var[4]) {
					case '1':
						switch (var[5]) {
							case '0':
								sscanf ((const char *)&var[7], "%d",&s[0]);
								indoor[9].room = s[0];
								break;
							
							case '1':
								sscanf ((const char *)&var[7], "%d",&s[0]);
								indoor[10].room = s[0];
								break;
							
							case '2':
								sscanf ((const char *)&var[7], "%d",&s[0]);
								indoor[11].room = s[0];
								break;
							
							case '=':
								sscanf ((const char *)&var[6], "%d",&s[0]);
								indoor[0].room = s[0];
								break;
							
							default:
								break;
						}
						break;
					case '2':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[1].room = s[0];
						break;
					
					case '3':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[2].room = s[0];
						break;
					
					case '4':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[3].room = s[0];
						break;
					
					case '5':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[4].room = s[0];
						break;
					
					case '6':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[5].room = s[0];
						break;
					
					case '7':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[6].room = s[0];
						break;
					
					case '8':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[7].room = s[0];
						break;
					
					case '9':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[8].room = s[0];
						break;
					
					default:
						break;
				}
				// write to flash
			}
			else if (str_scomp (var, "port") == __TRUE) {
				switch (var[4]) {
					case '1':
						switch (var[5]) {
							case '0':
								sscanf ((const char *)&var[7], "%d",&s[0]);
								indoor[9].port = s[0];
								break;
							
							case '1':
								sscanf ((const char *)&var[7], "%d",&s[0]);
								indoor[10].port = s[0];
								break;
							
							case '2':
								sscanf ((const char *)&var[7], "%d",&s[0]);
								indoor[11].port = s[0];
								break;
							
							case '=':
								sscanf ((const char *)&var[6], "%d",&s[0]);
								indoor[0].port = s[0];
								break;
							
							default:
								break;
						}
						break;
					case '2':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[1].port = s[0];
						break;
					
					case '3':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[2].port = s[0];
						break;
					
					case '4':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[3].port = s[0];
						break;
					
					case '5':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[4].port = s[0];
						break;
					
					case '6':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[5].port = s[0];
						break;
					
					case '7':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[6].port = s[0];
						break;
					
					case '8':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[7].port = s[0];
						break;
					
					case '9':
						sscanf ((const char *)&var[6], "%d",&s[0]);
						indoor[8].port = s[0];
						break;
					
					default:
						break;
				}
				// write to flash
			}
			else if (str_scomp (var, "getinfo=") == __TRUE) {
        /* Get config infos from admin. */
				GETINFO = 1;
				TimerInit(1, CON_INTERVAL);
				enTimer(1);
				return;
      }
			if (str_scomp (var, "pg=update") == __TRUE) {
				refresh_update(__TRUE);
			}
    }
  }while (qs);
	free_mem ((OS_FRAME *)var);
	refresh_update(__FALSE);
}


/*--------------------------- cgi_process_data ------------------------------*/

void cgi_process_data (U8 code, U8 *dat, U16 len) {
  /* This function is called by HTTP server to process the returned Data    */
  /* for the CGI Form POST method. It is called on SUBMIT from the browser. */
  /* Parameters:                                                            */
  /*   code  - callback context code                                        */
  /*           0 = www-url-encoded form data                                */
  /*           1 = filename for file upload (0-terminated string)           */
  /*           2 = file upload raw data                                     */
  /*           3 = end of file upload (file close requested)                */
  /*           4 = any xml encoded POST data (single or last stream)        */
  /*           5 = the same as 4, but with more xml data to follow          */
  /*               Use http_get_content_type() to check the content type    */  
  /*   dat   - pointer to POST received data                                */
  /*   len   - received data length                                         */
  U8 passw[12],retyped[12];
  U8 *var,stpassw;

  switch (code) {
    case 0:
      /* Url encoded form data received. */
      break;

    default:
      /* Ignore all other codes. */
      return;
  }

  if (len == 0) {
    /* No data or all items (radio, checkbox) are off. */
    return;
  }
  stpassw = 0;
  var = (U8 *)alloc_mem (40);
  do {
    /* Parse all returned parameters. */
    dat = http_get_var (dat, var, 40);
    if (var[0] != 0) {
      /* Parameter found, returned string is non 0-length. */
      if (str_scomp (var, "pw=") == __TRUE) {
        /* Change password. */
        str_copy (passw, var+3);
        stpassw |= 1;
      }
      else if (str_scomp (var, "pw2=") == __TRUE) {
        /* Retyped password. */
        str_copy (retyped, var+4);
        stpassw |= 2;
      }
    }
  }while (dat);
  free_mem ((OS_FRAME *)var);

  if (stpassw == 0x03) {
    len = strlen ((const char *)passw);
    if (mem_comp (passw, retyped, len) == __TRUE) {
      /* OK, both entered passwords the same, change it. */
      str_copy (http_auth_passw, passw);
    }
  }
}


/*--------------------------- cgi_func --------------------------------------*/

U16 cgi_func (U8 *env, U8 *buf, U16 buflen, U32 *pcgi) {
  /* This function is called by HTTP server script interpreter to make a    */
  /* formated output for 'stdout'. It returns the number of bytes written   */
  /* to the output buffer. Hi-bit of return value (len is or-ed with 0x8000)*/
  /* is a repeat flag for the system script interpreter. If this bit is set */
  /* to 1, the system will call the 'cgi_func()' again for the same script  */
  /* line with parameter 'pcgi' pointing to a 4-byte buffer. This buffer    */
  /* can be used for storing different status variables for this function.  */
  /* It is set to 0 by HTTP Server on first call and is not altered by      */
  /* HTTP server for repeated calls. This function should NEVER write more  */
  /* than 'buflen' bytes to the buffer.                                     */
  /* Parameters:                                                            */
  /*   env    - environment variable string                                 */
  /*   buf    - HTTP transmit buffer                                        */
  /*   buflen - length of this buffer (500-1400 bytes - depends on MSS)     */
  /*   pcgi   - pointer to session local buffer used for repeated loops     */
  /*            This is a U32 variable - size is 4 bytes. Value is:         */
  /*            - on 1st call = 0                                           */
  /*            - 2nd call    = as set by this function on first call       */
  U32 len = 0;

  switch (env[0]) {
    /* Analyze the environment string. It is the script 'c' line starting */
    /* at position 2. What you write to the script file is returned here. */
    case 'a' :
      /* Network parameters - file 'network.cgi' */
      switch (env[2]) {
        case 'i':
          /* Write the local IP address. The format string is included */
          /* in environment string of the script line.                 */
          len = sprintf((char *)buf,(const char *)&env[4],nlocalm[0].IpAdr[0],
                        nlocalm[0].IpAdr[1],nlocalm[0].IpAdr[2],nlocalm[0].IpAdr[3]);
          break;
				
        case 'm':
          /* Write local Net mask. */
          len = sprintf((char *)buf,(const char *)&env[4],nlocalm[0].NetMask[0],
                        nlocalm[0].NetMask[1],nlocalm[0].NetMask[2],nlocalm[0].NetMask[3]);
          break;
				
        case 'g':
          /* Write default gateway address. */
          len = sprintf((char *)buf,(const char *)&env[4],nlocalm[0].DefGW[0],
                        nlocalm[0].DefGW[1],nlocalm[0].DefGW[2],nlocalm[0].DefGW[3]);
          break;
				
        case 'p':
          /* Write primary DNS server address. */
          len = sprintf((char *)buf,(const char *)&env[4],nlocalm[0].PriDNS[0],
                        nlocalm[0].PriDNS[1],nlocalm[0].PriDNS[2],nlocalm[0].PriDNS[3]);
          break;
				
        case 's':
          /* Write secondary DNS server address. */
          len = sprintf((char *)buf,(const char *)&env[4],nlocalm[0].SecDNS[0],
                        nlocalm[0].SecDNS[1],nlocalm[0].SecDNS[2],nlocalm[0].SecDNS[3]);
          break;
				
				case 't':
					len = sprintf((char *)buf,(const char *)&env[4],Server.IP[0],
                        Server.IP[1],Server.IP[2],Server.IP[3]);
          break;
				
				case 'a':
					len = sprintf((char *)buf,(const char *)&env[4],Admin.IP[0],
                        Admin.IP[1],Admin.IP[2],Admin.IP[3]);
          break;
				
				case 'o':
					len = sprintf((char *)buf,(const char *)&env[4],Outdoor.IP[0],
                        Outdoor.IP[1],Outdoor.IP[2],Outdoor.IP[3]);
          break;
      }
      break;

    case 'b':
      /* Configports - file 'configports.cgi' */
			switch (env[2]) {
				case 'a':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[0].room);
					break;
				
				case 'b':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[0].port);
					break;
				
				case 'c':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[1].room);
					break;
				
				case 'd':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[1].port);
					break;
				
				case 'e':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[2].room);
					break;
				
				case 'f':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[2].port);
					break;
				
				case 'g':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[3].room);
					break;
				
				case 'h':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[3].port);
					break;
				
				case 'i':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[4].room);
					break;
				
				case 'j':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[4].port);
					break;
				
				case 'k':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[5].room);
					break;
				
				case 'l':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[5].port);
					break;
				
				case 'm':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[6].room);
					break;
				
				case 'n':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[6].port);
					break;
				
				case 'o':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[7].room);
					break;
				
				case 'p':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[7].port);
					break;
				
				case 'q':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[8].room);
					break;
				
				case 'r':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[8].port);
					break;
				
				case 's':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[9].room);
					break;
				
				case 't':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[9].port);
					break;
				
				case 'u':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[10].room);
					break;
				
				case 'v':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[10].port);
					break;
				
				case 'w':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[11].room);
					break;
				
				case 'x':
					len = sprintf((char *)buf,(const char *)&env[4],indoor[11].port);
					break;
			}
      break;

    case 'd':
      /* System password - file 'system.cgi' */
      switch (env[2]) {
        case '1':
          len = sprintf((char *)buf,(const char *)&env[4],
                        http_EnAuth ? "已开启" : "已关闭");
          break;
				
        case '2':
          len = sprintf((char *)buf,(const char *)&env[4],http_auth_passw);
          break;
      }
      break;
			
		case 'e':
			len = sprintf((char *)buf,(const char *)&env[2],version);
			break;
  }
  return ((U16)len);
}


/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
