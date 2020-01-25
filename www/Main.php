<?php
// PHP7/HTML5, EDGE/CHROME                                     *** Main.php ***

// ****************************************************************************
// * ByHeart        Страницы-шпаргалки для помощи при программировании сайтов *
// *      на PHP, JavaScript с использованием библиотек TPhpPrown, TPhpTools, *
// *                                           TJsPrown и других инструментов *
// ****************************************************************************

/*
// Подключаем задействованные классы
require_once $SiteHost."/TPhpTools/TPageStarter/PageStarterClass.php";
// Подключаем рабочие модули сайта 
require_once $SiteRoot."/ComRequest.php";
//require_once $SiteRoot."/DebugError.php";
require_once $SiteRoot."/IniCurrStih.php";
require_once $SiteRoot."/IniTPhpPrown.php";
require_once $SiteRoot."/IniMenu.php";
require_once $SiteRoot."/MakeQrcode.php"; 
*/

//\prown\ViewGlobal(avgSESSION);
//\prown\ViewGlobal(avgGLOBALS);

// Запускаем нужную страницу
require_once $_SERVER['DOCUMENT_ROOT'].'/Pages/ByHeart/PhpIni/PhpIni.php';

//$page='/Pages/ByHeart/PhpIni/PhpIni.php';
//Header("Location: http://".$_SERVER['HTTP_HOST'].$page);
//echo "Location: http://".$_SERVER['HTTP_HOST'].$page.'<br>';
// *************************************************************** Main.php ***
