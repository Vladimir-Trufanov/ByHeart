<?php namespace prown;

// PHP7/HTML5, EDGE/CHROME                                *** CtrlArray.php ***

// ****************************************************************************
// * TPHPPROWN            Инициализировать/обновить значение простого массива *
// *                         по кукису или параметрам с контролем размерности, *
// *                                       но без проверки значений элементов *
// ****************************************************************************


//                                 УСТАРЕЛО


//                                                   Автор:       Труфанов В.Е.
//                                                   Дата создания:  26.02.2018
// Copyright © 2018 tve                              Посл.изменение: 12.03.2018

// Функция работает с "простыми" массивами ("порядковый номер" -> "значение")

// "Проживающие" -             Кукис из                   Параметр 
// рабочий массив              сеарилизованного массива   с порядковым номером
// $aZhFio[0]='ФОТЕЕВА Н.П.'   $_COOKIE["aZhFio"]         zhFio0='ФОТЕЕВА Н.П.'
// $aZhFio[1]='СИДОРЕНКО И.М.'                            zhFio1='СИДОРЕНКО И.М.'

// $aZhLgokat[0]=202;          $_COOKIE["aZhLgokat"]      zhLgokat0=202;
// $aZhLgokat[1]=118;                                     zhLgokat1=118;

function CtrlArray(&$RowCount,$CookieCount,&$aArray,$CookieName,$RequestName,
    $MaxCount=1000,$IsCookie=True,&$Err=0)

// $RowCount - число элементов массива
// $CookieCount - имя кукиса с числом элементов массива
// $Array - уже инициализированный массив
// $CookieName - имя кукиса сериализированного массива
// $RequestName - имя параметра (без порядкого номера)
// $MaxCount - максимальное число элементов массива
// $IsCookie=True - заменить инициализированный массив массивом из кукисов

// $Err=0 - "все в порядке, отработано успешно"
// $Err=1 - "номер элемента из параметра превышает разрешенный в массиве"
// $Err=2 - "размерность масива из кукиса превышает разрешенную"
// $Err=4 - "номер элемента из параметра превышает фактический в массиве"

{
    $Err=0;         // "все в порядке, отработано успешно"
    $isDelta=False; // в начале считаем, что перезаписывать массив в кукисы не нужно  

    // Перезаполняем инициализированный массив элементами из кукисов
    // через рабочий массив
    $arr=array();  
    if ($IsCookie)      
    {
        // Если прообраз массива есть в кукисах, то выбираем их оттуда
        if (IsSet($_COOKIE[$CookieName]))
        {
            $arr = unserialize($_COOKIE[$CookieName]);
            // Трассируем размерность массива из кукиса
            // echo '<br>'.'count($arr)='.count($arr);
            // Ограничиваем массив из кукиса максимальным номером элемента
            if (count($arr)<=$MaxCount) $aArray=$arr;
            else 
            {
                $Err=$Err+2;
                $arrCopy=array();
                foreach($arr as $key => $value)
                {
                    if ($key<$MaxCount) $arrCopy[$key]=$value;
                }
                $aArray=$arrCopy; 
            }
        }
    }
    // Так как инициирование из кукисов отключено, 
    // будем умалчиваемый массив перезаписывать в кукисы
    else $isDelta=True;
    
    // Трассируем выбранный массив 
    // ViewArray($aArray,'In: '.$CookieName);

    // Если в параметрах передавались значения, отличающиеся от
    // значений в массивах, то меняем значения в массивах и
    // сохраняем сериализованные массивы в кукисах

    // Перебираем параметры, ищем элементы массива и сравниваем 
    foreach($_REQUEST as $key => $value) 
    {
        // Трассируем выбираемые значения
        //echo '<br>'.'CtrlArray: '.$key.'=>'.$value;
        // Отлавливаем параметы массива
        $reg="/".$RequestName.'\d+'."/u"; 
        //echo '<br>'.'$reg='.$reg;
        //if (regx($reg,$key,$matches,false)) 
        if (preg_match($reg,$key,$matches)) 
        {
            //$elem=$matches[0][0][0];
            $elem=$matches[0];
            // echo '$elem='.$elem; 
            // Выбираем номер элемента массива
            $reg="/".'\d+'."/u"; 
            if (preg_match($reg,$key,$matches)) 
            {
                $num=$matches[0];
                // Номер и имя элемента ограничиваем максимальным размером массива
                if ($num>=$MaxCount) 
                {
                    $num=$MaxCount-1;
                    $elem="$RequestName"."$num";
                    $RowCount=$MaxCount;
                    $Err=$Err+1;
                }
                // Трассируем выбранные элементы
                // echo '<br>'.
                //    '$RowCount='.$RowCount.' $MaxCount='.$MaxCount.'  '.
                //    $elem.'['.$num.']='.$value;
                
                // Проверяем есть ли переданный параметр (по номеру) в массиве
                if (!(IsSet($aArray[$num])))
                {
                    $Err=$Err+4;
                    $aArray[$num]=$value;
                    $isDelta=True;    
                }
                // Проверяем, отличается ли значение параметра от 
                // значения в массиве, при отличии меняем
                if (!($aArray[$num]==$value)) 
                {
                    $aArray[$num]=$value;
                    $isDelta=True;    
                }
                
            }
        }
    }

    // Трассируем массив после проверки 
    // ViewArray($aArray,'Ou: '.$CookieName);
    
    // Если отличия были, то сохраняем в кукисах сериализованный массив
    $aVali='';   // cериализованный массив, отправляемый в кукис
    if ($isDelta)
    {
        $aVali=serialize($aArray);
        MakeCookie($CookieName,$aVali);
    }
    
    // Перезаписываем кукис количества элементов
    if (!($RowCount==count($aArray)))
    {
        $RowCount=count($aArray);
        MakeCookie($CookieCount,$RowCount); 
    }
}
// ********************************************************** CtrlArray.php ***

