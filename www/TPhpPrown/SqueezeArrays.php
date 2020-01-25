<?php namespace prown;

// PHP7/HTML5, EDGE/CHROME                            *** SqueezeArrays.php ***

// ****************************************************************************
// * TPHPPROWN                        Поджать массивы до заданной размерности *
// ****************************************************************************

//                                                   Автор:       Труфанов В.Е.
//                                                   Дата создания:  08.03.2018
// Copyright © 2018 tve                              Посл.изменение: 03.04.2018

// Функция работает с "простыми" массивами ("порядковый номер" -> "значение")

// "Проживающие" -             Кукис из                   Параметр 
// рабочий массив              сеарилизованного массива   с порядковым номером
// $aZhFio[0]='ФОТЕЕВА Н.П.'   $_COOKIE["aZhFio"]         zhFio0='ФОТЕЕВА Н.П.'
// $aZhFio[1]='СИДОРЕНКО И.М.'                            zhFio1='СИДОРЕНКО И.М.'

// $aZhLgokat[0]=202;          $_COOKIE["aZhLgokat"]      zhLgokat0=202;
// $aZhLgokat[1]=118;                                     zhLgokat1=118;

function _SqueezeArrays($Array,$Dim)
{
    $i=0; $arr=array();
    foreach($Array as $key => $value) 
    {
        $arr[]=$value; 
        $i++;
        if ($i>=$Dim) break;
    }
    return $arr;
}

function SqueezeArrays($Arrays,$Dim)
{
    // Сжимаем массивы
    for ($i=0; $i<Count($Arrays); $i++)
    {
        $arr[$i]=_SqueezeArrays($Arrays[$i],$Dim);
    }
    // Собираем массивы вместе
    $Arrs=array();
    for ($i=0; $i<Count($arr); $i++)
    {
        $Arrs[]=$arr[$i];
    }
    return $Arrs;
}

// ****************************************************** SqueezeArrays.php ***

