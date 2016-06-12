t <html><head><title>登陆设置</title>
t <script language=JavaScript>
t function changeConfirm(f){
t  if(!confirm('确认修改登陆密码？')) return;
t  f.submit();
t }
t </script></head>
i pg_header.inc
t <h1 align=center><br>登陆设置</h1>
t <iframe name="none" style="display:none;" src=' '></iframe>
t <form action=index.htm method=post name=cgi target=none>
t <input type=hidden value="sys" name=pg>
t <table border=0 cellspacing=16 width=60% align="center" style="font-size:18px">
# Here begin data setting which is formatted in HTTP_CGI.C module
c d 1 <tr><td align="right" width=50%><img src=pabb.gif>登陆认证</TD><TD align=left width=50%><b>%s</b></td></tr>
t <tr><td align="right" width=50%><img src=pabb.gif>请输入新密码</td>
c d 2 <td align="left" width=50%><input type=password name=pw size=10 maxlength=10 value="%s"></td></tr>
t <tr><td align="right" width=50%><img src=pabb.gif>请确认新密码</td>
c d 2 <td align="left" width=50%><input type=password name=pw2 size=10 maxlength=10 value="%s"></td></tr>
t </font></table>
# Here begin button definitions
t <p align=center>
t <input type=button name=set value="修改" onclick="changeConfirm(this.form)">
t <input type=reset value="取消">
t </p></form>
i pg_footer.inc
. End of script must be closed with period.
