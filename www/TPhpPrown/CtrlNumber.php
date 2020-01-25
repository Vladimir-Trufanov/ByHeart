<?php namespace prown;

// PHP7/HTML5, EDGE/CHROME                               *** CtrlNumber.php ***

// ****************************************************************************
// * KwinFlat.ru           Инициализировать, проверить(преобразовать) данное, *
// *                                                     как десятичное число * 
// ****************************************************************************

//                                                   Автор:       Труфанов В.Е.
//                                                   Дата создания:  01.11.2017
// Copyright © 2017 tve                              Посл.изменение: 09.03.2018

function _CtrlNumber($Ini,$Min,$Max,$Cookie,$Dec,&$Err)
{
    // Контроллируем количество десятичных разрядов
    $Err=0; // все в порядке, ошибок нет
    if ($Dec<0) {$Dec=2; $Err=100;}
    elseif ($Dec>14) {$Dec=2; $Err=200;}
    // Выбираем число из параметра
    if (preg_match("/[0-9]{0,}\.*[0-9]{0,".$Dec."}/u",$Ini,$matches)) 
    {
        $tmp=$matches[0];
        // Проверяем по диапазону
        if ($tmp<$Min) 
        {
            $tmp=null;
            $Err=$Err+2; // число меньше минимума
        }
        elseif ($tmp>$Max) 
        {
            $tmp=null;
            $Err=$Err+3; // число больше максимума
        }
        // Все в порядке, записываем значение в кукис 
        else 
        {
            MakeCookie($Cookie,$tmp); 
        }
    }
    // Число не выбралось, ошибка
    else 
    {
        $tmp=null;
        $Err=$Err+1; // число из параметра не выбралось
    }
    $Result=$tmp;
    return $Result;
}

// Инициализировать, проверить(преобразовать) данное, как десятичное число 
function CtrlNumber($Ini=0,$Min=0,$Max=99999.99,$Cookie=null,$Parm=null,$Dec=2,&$Err=0)

// $Ini - значение данного по умолчанию для инициализации
// $Min - минимальное значение
// $Max - максимальное значение
// $Cookie - имя кукиса
// $Parm - имя параметра
// $Dec - число разрядов после точки
// $Err - код ошибки (0-все нормально, число проверено)

{
    $Err=0; // все в порядке, ошибок нет
    $Result=$Ini; $tmp=$Result;
    if (IsSet($_POST[$Parm])) 
    {
        $tmp=_CtrlNumber($_POST[$Parm],$Min,$Max,$Cookie,$Dec,$Err); 
    }                  
    elseif (IsSet($_GET[$Parm])) 
    {
        $tmp=_CtrlNumber($_GET[$Parm],$Min,$Max,$Cookie,$Dec,$Err); 
    } 
    // Выбираем значение из кукиса
    elseif (IsSet($_COOKIE[$Cookie])) 
    {
        $tmp=_CtrlNumber($_COOKIE[$Cookie],$Min,$Max,$Cookie,$Dec,$Err); 
    } 
    if (!($tmp==null)) $Result=$tmp;
    return $Result;
}

//echo "<br>".'outVeriDomikva';

// ********************************************************* CtrlNumber.php *** 

