t <html><head><title>��������</title>
t <script language=JavaScript>
t function changeConfirm(f){
t  if(!confirm('ȷ���޸��������ã�')) return;
t  f.submit();
t }
t </script></head>
i pg_header.inc
t <h1 align=center><br>��������</h1>
t <iframe name="none" style="display:none;" src=' '></iframe>
t <form action=network.cgi method=get name=cgi target=none>
t <input type=hidden value="net" name=pg>
t <table border=0 cellspacing=16 width=60% align="center" style="font-size:18px">
# Here begin data setting which is formatted in HTTP_CGI.C module
t <tr><td align="right" width=50%><img src=pabb.gif>����IP��ַ</td>
c a i <td align="left" width=50%><input type=text name=ip value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>��������</td>
c a m <td align="left" width=50%><input type=text name=msk value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>Ĭ������</td>
c a g <td align="left" width=50%><input type=text name=gw value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>��ѡDNS������</td>
c a p <td align="left" width=50%><input type=text name=pdns value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>����DNS������</td>
c a s <td align="left" width=50%><input type=text name=sdns value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>���������IP��ַ</td>
c a t <td align="left" width=50%><input type=text name=sip value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>��������IP��ַ</td>
c a a <td align="left" width=50%><input type=text name=aip value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>�ſڻ�IP��ַ</td>
c a o <td align="left" width=50%><input type=text name=oip value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t </font></table>
# Here begin button definitions
t <p align=center>
t <input type=button name=set value="����" onclick="changeConfirm(this.form)">
t <input type=reset value="ȡ��">
t </p></form>
i pg_footer.inc
. End of script must be closed with period.

