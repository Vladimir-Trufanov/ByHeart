<?php
// PHP7/HTML5, EDGE/CHROME                                   *** PhpIni.php ***

// ****************************************************************************
// * ByHeart                                          Путеводитель по Php.ini *
// ****************************************************************************

//                                                   Автор:       Труфанов В.Е.
//                                                   Дата создания:  24.01.2020
// Copyright © 2020 tve                              Посл.изменение: 25.01.2020

require_once "iniPhpIni.php";
require_once "iniHtmlBegin.php";
?> 

<div id="Gallery">
   <?php
   echo 'require_once "GalleryView.php"';
   ?> 
</div>

<div id="News">
   <?php
   echo 'require_once "Pages/tveArt/tve2-114-po-trope-k-karnizu-reki-bzerp.html"';
   require_once $SiteRoot."/MainDoorTry.php";
   ?>
</div>

<div id="Life">
   <?php
   echo 'require_once "Pages/tveArc1/tve1-1-оsobennosti-ustrojstva-vintikov-v-moej-golove.html"';
   ?>
</div>

<?php
require_once "iniHtmlEnd.php";

// <!-- --> **************************************************** PhpIni.php ***
