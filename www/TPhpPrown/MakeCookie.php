<?php namespace prown; 
                                         
// PHP7/HTML5, EDGE/CHROME                               *** MakeCookie.php ***

// ****************************************************************************
// * TPhpPrown                   Установить новое значение COOKIE в браузере, *
// *                   заменить это значение во внутреннем массиве $_COOKIE и *
// *                   установить новое значение переменной-кукиса в сценарии *
// *                                                                          *
// * v1.2, 31.05.2019                              Автор:       Труфанов В.Е. *
// * Copyright © 2018 tve                          Дата создания:  03.02.2018 *
// ****************************************************************************

// Синтаксис:
//
//   $Result=MakeCookie($Name,$Value,$Type=tStr,$Init=false,$Duration=44236800);

// Параметры:
//
//   $Name     - имя кукиса в браузере клиента (как правило, по имени кукиса 
//      формируется глобальная переменная сайтовой страницы добавлением префикса
//      "с_". Например: "BrowEntry" --> "$с_BrowEntry");
//   $Value    - значение кукиса браузера, это же значение во внутреннем массиве
//      $_COOKIE и у соответствующей глобальной переменной сайтовой страницы;
//   $Type     - константа, определяющая тип значения: tArr, tObj, tInt, tFloat, 
//      tStr, tBool, tNull. По умолчанию - tStr;
//   $Init     = true, это означает, что требуется установить указанное значение 
//      кукиса, только в том случае, если кукиса еще не было. В обычных условиях
//      (по умолчанию, когда $Init=false) значение кукиса меняется всегда;
//   $Duration - время жизни кукиса (по умолчанию 44236800 = 512 дней =
//      512д*24ч*60м*60с)

// Возвращаемое значение: 
//
//   $Result  - установленное значение COOKIE в браузере, во внутреннем массиве
//      $_COOKIE и переменной-кукиса в сценарии сайтовой страницы

// Замечание: 
//
//   При изменении кукиса функцией setcookie меняется только значение кукиса в
// браузере, а значение его в массиве $_COOKIE остается без изменения. Поэтому 
// для синхронизации значений в этом случае следует использовать MakeCookie.

require_once "MakeType.php";

function _MakeCookie($Name,$Value,$Type,$Dur)
{
   $Result=MakeType($Value,$Type);
   $Duration=time()+$Dur;
   // Отправляем новое куки браузеру
   setcookie($Name,$Value,$Duration);
   /*
   ?>
   <script  language="JavaScript">
      var Name="<?php echo $Name; ?>";
      var Value="<?php echo $Value; ?>";
      var Duration="<?php echo $Duration; ?>";
      setcookie(Name,Value,Duration);
   </script>
   <?php
   */
   // Устанавливаем новое куки в массиве кукисов
   if (IsSet($_COOKIE[$Name])) $_COOKIE[$Name]=$Value;
   // Возвращаем новое куки на выход в переменную страницы сайта
   return $Result;
}

function MakeCookie($Name,$Value,$Type=tStr,$Init=false,$Duration=44236800)
{
   // Устанавливаем значение, если инициализация
   if ($Init==true) 
   {
      if (!(IsSet($_COOKIE[$Name]))) 
      {
         $Result=_MakeCookie($Name,$Value,$Type,$Duration);
      }
      else $Result=$_COOKIE[$Name];
   }
   // Устанавливаем значение в обычном режиме
   else {$Result=_MakeCookie($Name,$Value,$Type,$Duration);} 
   return $Result;
}
// ********************************************************* MakeCookie.php ***
 