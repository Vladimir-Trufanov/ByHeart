<?php
// PHP7/HTML5, EDGE/CHROME                                     *** Main.php ***

// ****************************************************************************
// * ByHeart        Страницы-шпаргалки для помощи при программировании сайтов *
// *      на PHP, JavaScript с использованием библиотек TPhpPrown, TPhpTools, *
// *                                           TJsPrown и других инструментов *
// ****************************************************************************

//                                                   Автор:       Труфанов В.Е.
//                                                   Дата создания:  24.01.2020
// Copyright © 2020 tve                              Посл.изменение: 25.01.2020
      
// Инициализируем надсайтовый каталог и каталог хостинга
require_once "iGetAbove.php";
$SiteAbove = iGetAbove($SiteRoot);      // Надсайтовый каталог
$SiteHost = iGetAbove($SiteAbove);      // Каталог хостинга

/*
// Подключаем файлы библиотеки прикладных модулей
require_once $SiteRoot."/TPhpPrown/Findes.php";
require_once $SiteRoot."/TPhpPrown/getSiteDevice.php";
require_once $SiteRoot."/TPhpPrown/getTranslit.php";
require_once $SiteRoot."/TPhpPrown/iniConstMem.php";
require_once $SiteRoot."/TPhpPrown/MakeCookie.php";
require_once $SiteRoot."/TPhpPrown/MakeParm.php";
require_once $SiteRoot."/TPhpPrown/MakeSession.php";
require_once $SiteRoot."/TPhpPrown/ViewGlobal.php";
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
$page='/Pages/Proba/ProbaTest.php';
//Header("Location: http://".$_SERVER['HTTP_HOST'].$page);
echo ("Location: http://".$_SERVER['HTTP_HOST'].$page);
// *************************************************************** Main.php ***
