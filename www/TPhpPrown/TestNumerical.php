<?php namespace prown;

// PHP7/HTML5, EDGE/CHROME                            *** TestNumerical.php ***

// ****************************************************************************
// * TPHPPROWN           Проверить значение на соответствие десятичному числу *
// ****************************************************************************

//                                                   Автор:       Труфанов В.Е.
//                                                   Дата создания:  08.03.2018
// Copyright © 2018 tve                              Посл.изменение: 05.04.2018

function TestNumerical($Value,$Default,$Dec)
{
    // Может и никогда не случится
    if (!IsSet($Value))
    {
        $elem=-1958; //$Default;
    }
                                                // здесь "*" говорит
    $reg="/-*[0-9]{0,}\.*[0-9]{0,".$Dec."}/u";  // о том, что "." или "-"
                                                // могут и не быть
    if (preg_match($reg,$Value,$matches)) 
    {
        // когда число есть
        $elem=MakeType($matches[0],tfloat);
        // когда пустая строка
        if ($elem=='') $elem=MakeType($Default,tfloat);
    }
    else
    {
        // когда нет результатов
        $elem=MakeType($Default,tfloat);
    }
    return $elem;
}

// ****************************************************** TestNumerical.php ***

