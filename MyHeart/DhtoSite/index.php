<?php
echo 'Привет!<br>';


/*
$conn = new mysqli("192.168.1.195", "arduino", "arduino", "arduino");   // Хостинг, пароль, логин, база
if ($conn->connect_error) {
die("Ошибка: не удается подключиться: " . $conn->connect_error);        // При невозможности подключения к базе
}
echo 'Подключение к базе данных *** Успешно ***.<br>';                  // Успешное подключение к базе

$result = $conn->query("SELECT id_dht22 FROM dht22");                   
echo "Количество строк: $result->num_rows";                             // Вывод количества строк в таблице dht22
*/

$page = 1;                                                              // 1 страница
if (isset($_GET['page'])){                                              // Создание переменной Страница из URL страницы
	$page = $_GET['page'];
}else $page = 1;


$count = 10;                                                             //количество записей для вывода
$all_rec = 5; //$result->num_rows;                                           //всего записей
$art = ($page * $count) - $count;
?>

<table  align=center width=700px>
<colgroup>
    <col span="1" style="background:Khaki">                         <!-- Фон первого столбца таблицы-->
    <col span="5" style="background-color:silver">                  <!-- Фон для следующего(следующих) столбца таблицы-->
</colgroup>
<caption><h3>Вывод информации с датчика</h3></caption>
  <tr align=center style="background:blue; color:white">
    <th>ID</th>
    <th>Дата</th>
    <th>Время</th>
    <th>Температура</th>
    <th>Влажность</th>
   </tr>

<?php 

//$result=$conn->query("SELECT * FROM dht22 ORDER BY id_dht22 DESC LIMIT $art,$count");           // Вывод всех значений из таблицы dht22 с сортировкой по убыванию
//while($myrow=$result->fetch_array(MYSQLI_ASSOC))
//{
//  $php_date = date("d/m/Y", strtotime($myrow['date_dht22']));     // Перевод даты в удобочитаемый формат
//  $php_time = date("H:i:s", strtotime($myrow['date_dht22']));     // Вывод времени
    echo"<tr style='font-weight: 600;' align=center>";
    echo"<td>";
    echo 1; //$myrow['id_dht22'];
    echo"</td>";
    echo"<td>";
    echo date("d/m/Y"); //$php_date;
    echo"</td>"; 
    echo"<td>";
    echo date("H:i:s"); //$php_time;
    echo"</td>"; 
    echo"<td>";
    echo 4; //$myrow['temp_dht22']."&degС";
    echo"</td>"; 
    echo"<td>";
    echo 5; //$myrow['hum_dht22']."%";
    echo"</td>";
    echo"</tr>";
    //}
?>
</table>

<?php
echo "<div align='center'>Страница ";                                      // Вывод навигатора страниц
for ($i = 1; $i <= $all_rec/$count+1; $i++){
  echo "<a href=index.php?page=".$i."> | ".$i." |</a>";
}
echo "</div>";
?>
<meta http-equiv="Refresh" content="10; URL=\">                  <!-- Перезагружаем страницу раз в 10 секунд  -->
