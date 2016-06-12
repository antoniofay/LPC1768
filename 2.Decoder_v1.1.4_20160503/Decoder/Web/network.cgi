t <html><head><title>网络设置</title>
t <script language=JavaScript>
t function changeConfirm(f){
t  if(!confirm('确认修改网络设置？')) return;
t  f.submit();
t }
t </script></head>
i pg_header.inc
t <h1 align=center><br>网络配置</h1>
t <iframe name="none" style="display:none;" src=' '></iframe>
t <form action=network.cgi method=get name=cgi target=none>
t <input type=hidden value="net" name=pg>
t <table border=0 cellspacing=16 width=60% align="center" style="font-size:18px">
# Here begin data setting which is formatted in HTTP_CGI.C module
t <tr><td align="right" width=50%><img src=pabb.gif>本地IP地址</td>
c a i <td align="left" width=50%><input type=text name=ip value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>子网掩码</td>
c a m <td align="left" width=50%><input type=text name=msk value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>默认网关</td>
c a g <td align="left" width=50%><input type=text name=gw value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>首选DNS服务器</td>
c a p <td align="left" width=50%><input type=text name=pdns value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>备用DNS服务器</td>
c a s <td align="left" width=50%><input type=text name=sdns value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>管理服务器IP地址</td>
c a t <td align="left" width=50%><input type=text name=sip value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>管理中心IP地址</td>
c a a <td align="left" width=50%><input type=text name=aip value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t <tr><td align="right" width=50%><IMG SRC=pabb.gif>门口机IP地址</td>
c a o <td align="left" width=50%><input type=text name=oip value="%d.%d.%d.%d" size=18 maxlength=18></td></tr>
t </font></table>
# Here begin button definitions
t <p align=center>
t <input type=button name=set value="保存" onclick="changeConfirm(this.form)">
t <input type=reset value="取消">
t </p></form>
i pg_footer.inc
. End of script must be closed with period.

