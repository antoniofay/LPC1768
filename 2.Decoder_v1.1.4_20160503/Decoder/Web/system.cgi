t <html><head><title>��½����</title>
t <script language=JavaScript>
t function changeConfirm(f){
t  if(!confirm('ȷ���޸ĵ�½���룿')) return;
t  f.submit();
t }
t </script></head>
i pg_header.inc
t <h1 align=center><br>��½����</h1>
t <iframe name="none" style="display:none;" src=' '></iframe>
t <form action=index.htm method=post name=cgi target=none>
t <input type=hidden value="sys" name=pg>
t <table border=0 cellspacing=16 width=60% align="center" style="font-size:18px">
# Here begin data setting which is formatted in HTTP_CGI.C module
c d 1 <tr><td align="right" width=50%><img src=pabb.gif>��½��֤</TD><TD align=left width=50%><b>%s</b></td></tr>
t <tr><td align="right" width=50%><img src=pabb.gif>������������</td>
c d 2 <td align="left" width=50%><input type=password name=pw size=10 maxlength=10 value="%s"></td></tr>
t <tr><td align="right" width=50%><img src=pabb.gif>��ȷ��������</td>
c d 2 <td align="left" width=50%><input type=password name=pw2 size=10 maxlength=10 value="%s"></td></tr>
t </font></table>
# Here begin button definitions
t <p align=center>
t <input type=button name=set value="�޸�" onclick="changeConfirm(this.form)">
t <input type=reset value="ȡ��">
t </p></form>
i pg_footer.inc
. End of script must be closed with period.
