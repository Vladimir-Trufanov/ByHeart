<?php namespace prown;

// PHP7/HTML5, EDGE/CHROME                            *** isSubstrInUri.php ***

// ****************************************************************************
// * TPHPPROWN          Проверить присутствие фрагмента в поступившем запросе *
// ****************************************************************************

//                                                   Автор:       Труфанов В.Е.
//                                                   Дата создания:  03.04.2018
// Copyright © 2018 tve                              Посл.изменение: 11.05.2018

function isSubstrInUri($subs)
{
    $Result=false;
    $str=$_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI'];
    // Ищем фрагмент в запросе
    $reg="/".$subs."/u"; 
    if (preg_match($reg,$str,$matches)) 
    {
        $Result=true;
    }
    return $Result;
}

// ****************************************************** isSubstrInUri.php ***

