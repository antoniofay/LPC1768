t <html><head><title>�������</title>
t <script language=JavaScript>
t function changeConfirm(f){
t  if(!confirm('����:���¹��̲�������ʹϵͳ����δ֪״̬��ȷ�ϸ��£�')) return;
t  f.submit();
t  alert('����ȷ�Ϲر���ҳ�����ȴ�Լ6���ʼ������£�');
t  setTimeout(timer(),1000);
t }
t function timer() {
t  window.opener=null;
t  window.open('', '_self', ''); 
t  window.close();
t }
t </script></head>
i pg_header.inc
t <h1 align=center><br>�������</h1>
t <iframe name="none" style="display:none;"></iframe>
t <form action=update.cgi method=get name=cgi target=none>
t <input type=hidden value="update" name=pg>
t <table border=0 cellspacing=16 width=60% align="center" style="font-size:18px">
t <tr><td align="right" width=50%><img src=pabb.gif>ϵͳ��ǰ�汾</td>
c e <td align="left" width=50%>%s</td></tr>
t </font></table>
# Here begin button definitions
t <p align=center>
t <input type=button name=set value="����" onclick="changeConfirm(this.form)">
t </p>
t <p align=center><b>�ύ�����������ȴ�Լ6�����г������</b>
t </p></form>
i pg_footer.inc
. End of script must be closed with period.

