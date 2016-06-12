t <html><head><title>程序更新</title>
t <script language=JavaScript>
t function changeConfirm(f){
t  if(!confirm('警告:更新过程不当可能使系统进入未知状态，确认更新？')) return;
t  f.submit();
t  alert('请点击确认关闭网页，并等待约6秒后开始程序更新！');
t  setTimeout(timer(),1000);
t }
t function timer() {
t  window.opener=null;
t  window.open('', '_self', ''); 
t  window.close();
t }
t </script></head>
i pg_header.inc
t <h1 align=center><br>程序更新</h1>
t <iframe name="none" style="display:none;"></iframe>
t <form action=update.cgi method=get name=cgi target=none>
t <input type=hidden value="update" name=pg>
t <table border=0 cellspacing=16 width=60% align="center" style="font-size:18px">
t <tr><td align="right" width=50%><img src=pabb.gif>系统当前版本</td>
c e <td align="left" width=50%>%s</td></tr>
t </font></table>
# Here begin button definitions
t <p align=center>
t <input type=button name=set value="更新" onclick="changeConfirm(this.form)">
t </p>
t <p align=center><b>提交更新请求后请等待约6秒后进行程序更新</b>
t </p></form>
i pg_footer.inc
. End of script must be closed with period.

