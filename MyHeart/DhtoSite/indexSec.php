<?php
<?php

/*
$conn = new mysqli("192.168.1.195", "arduino", "arduino", "arduino");   // �������, ������, �����, ����
if ($conn->connect_error) {
die("������: �� ������� ������������: " . $conn->connect_error);        // ��� ������������� ����������� � ����
}
echo '����������� � ���� ������ *** ������� ***.<br>';                  // �������� ����������� � ����

$result = $conn->query("SELECT id_dht22 FROM dht22");                   
echo "���������� �����: $result->num_rows";                             // ����� ���������� ����� � ������� dht22
*/

$page = 1;                                                              // 1 ��������
if (isset($_GET['page'])){                                              // �������� ���������� �������� �� URL ��������
	$page = $_GET['page'];
}else $page = 1;


$count = 10;                                                             //���������� ������� ��� ������
$all_rec = $result->num_rows;                                           //����� �������
$art = ($page * $count) - $count;
?>

<table  align=center width=700px>
<colgroup>
    <col span="1" style="background:Khaki">                         <!-- ��� ������� ������� �������-->
    <col span="5" style="background-color:silver">                  <!-- ��� ��� ����������(���������) ������� �������-->
</colgroup>
<caption><h3>����� ���������� � �������</h3></caption>
  <tr align=center style="background:blue; color:white">
    <th>ID</th>
    <th>����</th>
    <th>�����</th>
    <th>�����������</th>
    <th>���������</th>
   </tr>

<?php 

//$result=$conn->query("SELECT * FROM dht22 ORDER BY id_dht22 DESC LIMIT $art,$count");           // ����� ���� �������� �� ������� dht22 � ����������� �� ��������
//while($myrow=$result->fetch_array(MYSQLI_ASSOC))
//{
//  $php_date = date("d/m/Y", strtotime($myrow['date_dht22']));     // ������� ���� � ������������� ������
//  $php_time = date("H:i:s", strtotime($myrow['date_dht22']));     // ����� �������
    echo"<tr style='font-weight: 600;' align=center>";
    echo"<td>";
    echo 1; //$myrow['id_dht22'];
    echo"</td>";
    echo"<td>";
    echo date("d/m/Y"); //$php_date;
    echo"</td>"; 
    echo"<td>";
    echo date("H:i:s"; //$php_time;
    echo"</td>"; 
    echo"<td>";
    echo 4; //$myrow['temp_dht22']."&deg�";
    echo"</td>"; 
    echo"<td>";
    echo 5; //$myrow['hum_dht22']."%";
    echo"</td>";
    echo"</tr>";
    //}
?>
</table>

<?php
echo "<div align='center'>�������� ";                                      // ����� ���������� �������
for ($i = 1; $i <= $all_rec/$count+1; $i++){
  echo "<a href=index.php?page=".$i."> | ".$i." |</a>";
}
echo "</div>";
?>
<meta http-equiv="Refresh" content="10; URL=\">                  <!-- ������������� �������� ��� � 10 ������  -->
