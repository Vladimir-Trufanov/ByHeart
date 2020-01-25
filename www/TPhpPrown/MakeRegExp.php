<?php namespace prown;

// PHP7/HTML5, EDGE/CHROME                               *** MakeRegExp.php ***

// ****************************************************************************
// * TPhpPrown     Отработать регулярное выражение на тексте и оттрассировать *
// *               разбор. Рекомендуется использовать только для трассировки. *
// * Для выборки подстроки по регулярному выражению следует пользоваться дру- *
// * гими функциями (например, Findes).
// *                                                                          *
// * v1.1, 21.05.2019                              Автор:       Труфанов В.Е. *
// * Copyright © 2018 tve                          Дата создания:  02.04.2018 *
// ****************************************************************************

require_once "iniErrMessage.php";
require_once "MakeUserError.php";

// Синтаксис:
//
//   MakeRegExp($pattern,$text,&$matches=null,$isTrass=false);

// Параметры:
//
//   $pattern - текст регулярного выражения;
//   $text    - текст, который должен быть обработан регулярным выражением;
//   $matches - массив найденных фрагментов и позиций их начала после работы
//      регулярного выражения (параметр по ссылке);
//   $isTrass=true, если следует выполнить трассировку найденных соответствий
//      регулярному выражению.

// Возвращаемое значение: 
//
//   $Result  - количество найденных соответствий регулярному выражению.
//      $Result=0, если соответствий не найдено. 

// Зарегистрированные ошибки/исключения:
//   
// 1 - "Устарела выборка подстроки регулярным выражением".

// ****************************************************************************
// *  Выполнить функцию preg_match_all, при необходимости, отттрассировать ее *
// ****************************************************************************
function MakeRegExp($pattern,$text,&$matches=null,$isTrass=false)
{
   $Prefix='TPhpPrown';
   // Ошибки:
   // Warning: preg_match_all(): No ending delimiter '/' found in 
   //        C:\Webservers\kwinflat-ru\www\TPHPPROWN\regx.php on line 17
   // Warning: preg_match_all(): Delimiter must not be alphanumeric or backslash in 
   //        C:\Webservers\kwinflat-ru\www\TPHPPROWN\regx.php on line 20
    
   // Выполняем регулярное выражение и получаем результаты поиска
   $Result=preg_match_all($pattern,$text,$imatches,PREG_OFFSET_CAPTURE);
   if (!($matches=null)) $matches=$imatches;

   // При трассировке показываем текст, шаблон поиска 
   if ($isTrass)
   {
      echo '<br>'.'$text: '.$text;
      echo '<br>'.'$pattern: '.$pattern;
      // Показываем нулевой результат, если поиск неудачный  
      if ($Result==0)
      {
         echo '<br>'.'$Result=0';
      }
      // Формируем и показываем массив найденных  результатов: 
      // что найдено и позиция
      else 
      {
         for ($i=0; $i<count($imatches); $i++)
		   {
            $findes=$imatches[$i];    
            for ($j=0; $j<count($findes); $j++)
            {
               echo '<br>$findes['.$j.'] = '.
               $findes[$j][0].' Point = '.
               $findes[$j][1];  
            }
         }
      }
      echo '<br>';
   }
   // Если трассировка не нужна, то выдаем сообщение:
   // "Устарела выборка подстроки регулярным выражением"
   else
   {
      //trigger_error($Prefix.': '.FetchStrObsolete,E_USER_DEPRECATED);
      \prown\MakeUserError(FetchStrObsolete,'TPhpPrown',0,E_USER_DEPRECATED);
   }   
   return $Result;
}
// ********************************************************* MakeRegExp.php ***
