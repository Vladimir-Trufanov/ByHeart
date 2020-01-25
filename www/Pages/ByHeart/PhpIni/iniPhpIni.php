<?php 
// PHP7/HTML5, EDGE/CHROME                                *** iniPhpIni.php ***

// ****************************************************************************
// * doortry.ru                   Произвести установки глобальных переменных, *
// *                                                подключить рабочие модули *
// ****************************************************************************

//                                                   Автор:       Труфанов В.Е.
//                                                   Дата создания:  24.01.2020
// Copyright © 2020 tve                              Посл.изменение: 25.01.2020

      
// Подключаем файлы библиотеки прикладных модулей
$TPhpPrown=$_SERVER['DOCUMENT_ROOT'];
//require_once $TPhpPrown."/TPhpPrown/Findes.php";
require_once $TPhpPrown."/TPhpPrown/getAbove.php";
require_once $TPhpPrown."/TPhpPrown/getSiteDevice.php";
/*
require_once $TPhpPrown."/TPhpPrown/getTranslit.php";
require_once $TPhpPrown."/TPhpPrown/iniConstMem.php";
require_once $TPhpPrown."/TPhpPrown/MakeCookie.php";
require_once $TPhpPrown."/TPhpPrown/MakeParm.php";
require_once $TPhpPrown."/TPhpPrown/MakeSession.php";
require_once $TPhpPrown."/TPhpPrown/ViewGlobal.php";
*/

// Инициализируем корневой каталог сайта, надсайтовый каталог и каталог хостинга
$SiteRoot=$_SERVER['DOCUMENT_ROOT'];
$SiteAbove=prown\getAbove($SiteRoot); // Надсайтовый каталог
$SiteHost=prown\getAbove($SiteAbove); // Каталог хостинга
//echo '***'.$SiteRoot.'***'.$SiteAbove.'***'.$SiteHost.'***<br>';

// Определяем сайтовые константы
define ("Computer", "Computer"); // "Устройство, запросившее сайт - компьютер"  
define ("Mobile", "Mobile");     // "Устройство, запросившее сайт - смартфон"  
define ("NotNews", "NotNews");   // "Новости неинициированы"  
define ("Tablet", "Tablet");     // "Устройство, запросившее сайт - планшет"  

// Инициализируем общие переменные сайтового сценария
$SiteDevice=prown\getSiteDevice();       // 'Computer','Mobile','Tablet'
$Uagent=$_SERVER['HTTP_USER_AGENT'];     // HTTP_USER_AGENT

// ********************************************************** iniPhpIni.php *** 
