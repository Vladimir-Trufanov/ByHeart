<?php namespace prown;

// PHP7/HTML5, EDGE/CHROME                          *** isCalcInBrowser.php ***
// ****************************************************************************
// * TPhpPrown    Проанализировать UserAgent браузера по версиям родительских *
// *                  браузеров и определить работает ли функция Calc для CSS *
// *                                                                          *
// * v1.0, 13.02.2019 (ревизия в 02.2020)          Автор:       Труфанов В.Е. *
// * Copyright © 2019 tve                          Дата создания:  13.02.2019 *
// ****************************************************************************

// Синтаксис:
//
//   $Result=isCalcInBrowser($UserAgent,$ModeError=rvsCurrentPos);
//
// Параметры:
//
//   $UserAgent - UserAgent браузера.
//   $ModeError - режим вывода сообщений об ошибке (по умолчанию в текущей 
//                позиции сайта)
// 
// Возвращаемое значение: 
//
//   $Result=true, если версии UserAgent показывают о возможности работы 
// функция Calc в CSS.
//
// Зарегистрированные ошибки/исключения:
//   
//   ManyBrowsersRec - "В UserAgent присутствует несколько браузеров";
//   InverBrowsers   - "Неверная или отсутствует версия браузера".

/*          Фрагменты содержимого UserAgent некоторых браузеров на 13.02.2019 и
                                         возможность работы функция Calc в CSS:

Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML,like Gecko)	

Chrome/56.0.2924.92  Safari/537.36 	                                 Орбитум  +
Сhrome/61.0.3163.69  Safari/537.36 Freeu/61.0.3163.69                  Freeu  +
Chrome/61.0.3163.79  Safari/537.36 Maxthon/5.2.6.1000	               Maxthon  +
Chrome/61.0.3163.125 Safari/537.36 Amigo/61.0.3163.125	              Amigo  +
Chrome/64.0.3282.140 Safari/537.36 Edge/17.17134                        Edge  +
Chrome/70.0.3538.102 Safari/537.36 OPR/57.0.3098.116	                 Opera  +
Chrome/71.0.3578.98  Safari/537.36	                                  Chrome  +
Chrome/71.0.3578.99  Safari/537.36 YaBrowser/19.1.0.2644 	          Yandex  +
		
Safari/534.57.2	                                                    Safari  -
Safari/537.21        QupZilla/1.8.6	                                QupZilla  -
		
Firefox/31.0         K-Meleon/75.1	                                K-Meleon  +
Firefox/65.0	                                                      Firefox  +

Trident/7.0                                                            Avant  -
*/

/**
 * Функция isCalcInBrowser указывает о возможности работы функция Calc в CSS, 
 * просматривая содержимое строки UserAgent, перебирая имена всех родительских 
 * браузеров и проверяя их версии.
 * 
 * Родительскими браузерами в функции isCalcInBrowser называются наименования 
 * браузеров, которые упоминает разработчик в строке UserAgent текущего 
 * браузера, то есть того, который показывает втекущий момент страницу сайта.
 * 
 * После приоритетного анализа версий браузеров принимается решение о наличии 
 * функции Calc в CSS  по следующему правилу:
 * 
 * а) вначале проверяем по браузеру Chrome. Если он указан и версия больше 55, 
 *    то Calc работает, иначе смотрим дальше;
 * б) проверяем по браузеру Safari. Если он указан и версия больше 537.35, 
 *    то Calc работает, иначе смотрим дальше;
 * в) проверяем по браузеру Firefox. Если он есть и версия больше 30, то Calc 
 *    работает;
 * г) в остальных случаях считаем, что Calc не работает. 
 * 
 * В случае противоречивой информации, например для UserAgent: 
 * 
 * Mozilla/5.0 (Windows NT 6.1; Win64; x86) AppleWebKit/537.36 (KHTML, 
 * like Gecko) Chrome/55.0.2883.87 Safari/537.36
 * 
 * определится, что функция Calc работает по Safari/537.36 (хотя по 
 * Chrome/55.0.2883.87 этого не следует). 
**/

require_once "iniConstMem.php";
require_once "iniErrMessage.php";
require_once "iniRegExp.php";
require_once "Findes.php";
require_once "MakeUserError.php";

// ****************************************************************************
// *             Собственно определить версию/подверсию браузера              *
// ****************************************************************************
function MakeNumbVer($Browser,$str,&$Ver,&$Point,$ModeError=rvsCurrentPos)
{
   $Point=0; 
   $Ver=\prown\Findes(regInteger,$str,$Point);
   if ($Ver=='')
   {
      \prown\MakeUserError(InverBrowsers.' ['.$Browser.', ver='.$str.']','TPhpPrown',$ModeError);
   }
}
// ****************************************************************************
// *     Определить присутствие браузера в UserAgent и выделить версию        *
// ****************************************************************************
function VerOneBrowser($UserAgent,$Browser,$ModeError=rvsCurrentPos)
{
   $Ver=0;
   $Result=false;
   $pattern="/".$Browser."/u";
   $value=preg_match_all($pattern,$UserAgent,$matches,PREG_OFFSET_CAPTURE);
   if ($value>1)
   {
      \prown\MakeUserError(ManyBrowsersRec.' ['.$Browser.'->'.$value.']','TPhpPrown',$ModeError);
      $Result=true;
   } 
   else if ($value==1)
   {
      $Result=true;
   }
   // Если браузер в UserAgent зарегистрирован,
   // то определяем версию 
   if ($Result)
   {
      $findes=$matches[0]; 
      // Вытаскиваем массив вхождений и определяем позицию последнего 
      // (или единственного) вхождения
      for ($i=0; $i<count($findes); $i++)
	   {
         $Point=$findes[$i][1];  
      }
      // Выделяем подстроку после имени браузера
      $str=substr($UserAgent,$Point+strlen($Browser)+1,8);
      // Определяем версию браузера и позицию в строке
      MakeNumbVer($Browser,$str,$Ver,$Point,$ModeError);
      // Для Safari получаем 5-разрядную версию
      if ($Browser=='Safari')
      {
         $Ver=$Ver*1000;
         $str=substr($str,$Point+4,4);
         MakeNumbVer($Browser,$str,$Ver2,$Point,$ModeError);
         $Ver=$Ver+$Ver2;
      }
   }
   return $Ver;
}
// ****************************************************************************
// *   Проанализировать UserAgent браузера по версиям родительских браузеров  *
// *               и определить работает ли функция Calc для CSS              *
// ****************************************************************************
function isCalcInBrowser($UserAgent,$ModeError=rvsCurrentPos)
{
   $Result=false;
   // Вначале проверяем по браузеру Chrome. Если он указан и версия больше 55,
   // то Calc работает, иначе смотрим дальше
   $Browser="Chrome";
   $Ver=VerOneBrowser($UserAgent,$Browser,$ModeError);
   if ($Ver>55)
   {
      $Result=true;
   }
   else
   {
      // Далее проверяем по браузеру Safari. Если он есть и версия больше 537.35,
      // то Calc работает, иначе смотрим дальше
      $Browser="Safari";
      $Ver=VerOneBrowser($UserAgent,$Browser,$ModeError);
      if ($Ver>537035)
      {
         $Result=true;
      }
      else
      {
         // Далее проверяем по браузеру Firefox. Если он есть и версия 
         // больше 30, то Calc работает, иначе смотрим дальше
         $Browser="Firefox";
         $Ver=VerOneBrowser($UserAgent,$Browser,$ModeError);
         if ($Ver>30)
         {
            $Result=true;
         }
         else
         {
         }
      }
   }
   return $Result;
}
// **************************************************** isCalcInBrowser.php ***
