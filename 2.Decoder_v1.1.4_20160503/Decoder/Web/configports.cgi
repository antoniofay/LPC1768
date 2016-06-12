t <html><head><title>¶Ë¿ÚÉèÖÃ</title>
t <script language=JavaScript>
t function changeConfirm(f){
t  if(!confirm('ÊÇ·ñÈ·¶¨¸ü¸Ä¶Ë¿ÚÉèÖÃÅ?')) return;
t  f.submit();
t }
t </script></head>
i pg_header.inc
t <h1 align=center><br>¶Ë¿ÚÉèÖÃ</h1>
t <iframe name="none" style="display:none;" src=' '></iframe>
t <center>
t <form action=configports.cgi method=get name=cgi target=none>
t <input type=submit name=getinfo value="»ñÈ¡ÅäÖÃĞÅÏ¢">
t </form></center>
t <form action=configports.cgi method=get name=cgi target=none>
t <input type=hidden value="configports" name=pg>
t <table border=0 cellspacing=12 align="center" width=60% style="font-size:18px">
t <tr>
t  <th align="right" width=50%>·¿ºÅ</th>
t  <th align="left" width=50%>¶Ë¿Ú</th></tr>
c b a <tr><td align="right"><img src=pabb.gif><input type=text name=room1 value="%d" size=18 maxlength=18></td>
c b b <td align="left"><input type=text name=port1 value="%d" size=18 maxlength=18></td></tr>
c b c <tr><td align="right"><img src=pabb.gif><input type=text name=room2 value="%d" size=18 maxlength=18></td>
c b d <td align="left"><input type=text name=port2 value="%d" size=18 maxlength=18></td></tr>
c b e <tr><td align="right"><img src=pabb.gif><input type=text name=room3 value="%d" size=18 maxlength=18></td>
c b f <td align="left"><input type=text name=port3 value="%d" size=18 maxlength=18></td></tr>
c b g <tr><td align="right"><img src=pabb.gif><input type=text name=room4 value="%d" size=18 maxlength=18></td>
c b h <td align="left"><input type=text name=port4 value="%d" size=18 maxlength=18></td></tr>
c b i <tr><td align="right"><img src=pabb.gif><input type=text name=room5 value="%d" size=18 maxlength=18></td>
c b j <td align="left"><input type=text name=port5 value="%d" size=18 maxlength=18></td></tr>
c b k <tr><td align="right"><img src=pabb.gif><input type=text name=room6 value="%d" size=18 maxlength=18></td>
c b l <td align="left"><input type=text name=port6 value="%d" size=18 maxlength=18></td></tr>
c b m <tr><td align="right"><img src=pabb.gif><input type=text name=room7 value="%d" size=18 maxlength=18></td>
c b n <td align="left"><input type=text name=port7 value="%d" size=18 maxlength=18></td></tr>
c b o <tr><td align="right"><img src=pabb.gif><input type=text name=room8 value="%d" size=18 maxlength=18></td>
c b p <td align="left"><input type=text name=port8 value="%d" size=18 maxlength=18></td></tr>
c b q <tr><td align="right"><img src=pabb.gif><input type=text name=room9 value="%d" size=18 maxlength=18></td>
c b r <td align="left"><input type=text name=port9 value="%d" size=18 maxlength=18></td></tr>
c b s <tr><td align="right"><img src=pabb.gif><input type=text name=room10 value="%d" size=18 maxlength=18></td>
c b t <td align="left"><input type=text name=port10 value="%d" size=18 maxlength=18></td></tr>
c b u <tr><td align="right"><img src=pabb.gif><input type=text name=room11 value="%d" size=18 maxlength=18></td>
c b v <td align="left"><input type=text name=port11 value="%d" size=18 maxlength=18></td></tr>
c b w <tr><td align="right"><img src=pabb.gif><input type=text name=room12 value="%d" size=18 maxlength=18></td>
c b x <td align="left"><input type=text name=port12 value="%d" size=18 maxlength=18></td></tr>
t </table>
# Here begin button definitions
t <p align=center>
t <input type=button name=set value="È·ÈÏ" onclick="changeConfirm(this.form)">
t <input type=reset value="È¡Ïû">
t </p></form>
i pg_footer.inc
. End of script must be closed with period.


