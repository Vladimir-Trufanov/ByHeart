<?php
// PHP7/HTML5, EDGE/CHROME                               *** iHtmlBegin.php ***

// ****************************************************************************
// * ByHeart                             Загрузить начало HTML для PhpIni.php * 
// *                              c подключением основного или мобильного CSS *
// ****************************************************************************

//                                                   Автор:       Труфанов В.Е.
//                                                   Дата создания:  24.01.2020
// Copyright © 2020 tve                              Посл.изменение: 25.01.2020

echo '<!DOCTYPE html>';
echo '<html lang="ru">';

echo '<head>';
echo '<meta http-equiv="content-type" content="text/html; charset=utf-8"/>';
echo '<title>Путеводитель по Php.ini</title>';
echo '<meta name="description" content="Путеводитель по Php.ini">';
echo '<meta name="keywords" content="Путеводитель по Php.ini, ByHeart>';

// Подключаем jquery/jquery-ui
echo '<link rel="stylesheet" type="text/css" '. 
     'href="https://code.jquery.com/ui/1.12.1/themes/ui-lightness/jquery-ui.css">';
echo '<script '.
     'src="https://code.jquery.com/jquery-3.3.1.min.js" '.
     'integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8=" '.
     'crossorigin="anonymous">'.
     '</script>';
echo '<script '.
     'src="https://code.jquery.com/ui/1.12.1/jquery-ui.min.js" '.
     'integrity="sha256-VazP97ZCwtekAsvgPBSUwPFKdrwD3unUfSGVYrahUqU=" '.
     'crossorigin="anonymous">'.
     '</script>';
// Делаем страницу для смартфона
if ($SiteDevice==Mobile) 
{   
   //echo '<script>alert("Mobile");</script>';
   //echo '<link href="Styles/MobiStyles.css" rel="stylesheet">';
}
// Делаем страницу для компьютера
else 
{   
   //echo '<script>alert("Computer");</script>';
   //echo '<link href="Styles/Styles.css" rel="stylesheet">';
}
// Подключаем вспомогательные JS
//echo '<link href="TJsPrown/TJsPrown.css" rel="stylesheet" type="text/css">'; 
//echo '<script src="/TJsPrown/TJsPrown.js"></script>';

echo '</head>';
echo '<body>';

// ********************************************************* iHtmlBegin.php ***
