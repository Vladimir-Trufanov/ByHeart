<?php namespace prown;

// PHP7/HTML5, EDGE/CHROME                            *** isCountArrays.php ***

// ****************************************************************************
// * TPHPPROWN       Проверить простые массивы на соответствие по размерности *
// *                                         и указать наименьшую размерность *
// ****************************************************************************

//                                                   Автор:       Труфанов В.Е.
//                                                   Дата создания:  08.03.2018
// Copyright © 2018 tve                              Посл.изменение: 03.04.2018

// Функция работает с "простыми" массивами ("порядковый номер" -> "значение")

// "Проживающие" -             Кукис из                   Параметр 
// рабочий массив              сериализованного массива   с порядковым номером
// $aZhFio[0]='ФОТЕЕВА Н.П.'   $_COOKIE["aZhFio"]         zhFio0='ФОТЕЕВА Н.П.'
// $aZhFio[1]='СИДОРЕНКО И.М.'                            zhFio1='СИДОРЕНКО И.М.'

// $aZhLgokat[0]=202;          $_COOKIE["aZhLgokat"]      zhLgokat0=202;
// $aZhLgokat[1]=118;                                     zhLgokat1=118;

function isCountArrays($Arrays,&$Dim)
{
    $Result=true;
    // Определяем размерности массивов
    $CtrlCount=Count($Arrays[0]); $Dim=Count($Arrays[0]);
    foreach($Arrays as $key => $value) 
    {
        if (!($CtrlCount==Count($value))) 
        {
            $Result=false;
            if (Count($value)<$Dim) $Dim=Count($value);
        }
        // echo "<br>".'$key='.$key.'  Count($value)='.Count($value).'  $Dim='.$Dim;
    }
    return $Result;
}
// ****************************************************** isCountArrays.php ***

