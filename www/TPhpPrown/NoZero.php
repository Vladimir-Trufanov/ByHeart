<?php namespace prown;

// PHP7/HTML5, EDGE/CHROME                                   *** NoZero.php ***

// ****************************************************************************
// * TPHPPROWN              Обеспечить вывод околонулевых значений в браузере *
// ****************************************************************************

//                                                   Автор:       Труфанов В.Е.
//                                                   Дата создания:  01.11.2016
// Copyright © 2016 TVE                              Посл.изменение: 28.02.2018

// Обеспечить вывод только числа
function NoZero($Value)
{
    $Result=" ";
    if ($Value<0)
	{
        if ($Value<-0.0001) $Result=$Value; 
    }
    if ($Value>0)
	{
        if ($Value>0.0001) $Result=$Value; 
    }
    //echo "<br>".'in.NoZero'."<br>";
    return $Result;
}
    
// Обеспечить вывод числа и связанной с ним дополнительной подстроки
function NoSpace($Value,$Ext)
{
    //echo "<br>".'$Value='.$Value.' $Ext='.$Ext."<br>";
    $Result=" ";
    if ($Value<0)
	{
        if ($Value<-0.0001) $Result="$Value"."$Ext"; 
    }
    if ($Value>0)
	{
        if ($Value>0.0001) $Result="$Value"."$Ext"; 
    }
    return $Result;
}

// echo "<br>".'out.NoZero'."<br>";
// ************************************************************* NoZero.php ***

