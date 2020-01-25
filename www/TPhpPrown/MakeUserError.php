<?php namespace prown;

// PHP7/HTML5, EDGE/CHROME                            *** MakeUserError.php ***
// ****************************************************************************
// * TPhpPrown     Вывести сообщение разработчика об ошибке в программируемом *
// *                      модуле или сформировать пользовательское исключение *
// *                                                                          *
// * v1.4, 12.01.2020                              Автор:       Труфанов В.Е. *
// * Copyright © 2019 tve                          Дата создания:  17.02.2019 *
// ****************************************************************************

require_once "iniConstMem.php";    

// Синтаксис
//
//   MakeUserError($Mess,$Prefix='TPhpPrown',$Mode=0,$errtype=E_USER_ERROR,$div='Ers')

// Параметры
//
//   $Mess    - текст сообщения об ошибке/исключении;
//   $Prefix  - префикс сообщения, указывающий на программную систему, в модуле
//              которой возникла ошибка/исключение;
//   $Mode    - режим вывода сообщений: rvsCurrentPos, rvsTriggerError, 
//              rvsMakeDiv,rvsDialogWindow;
//   $errtype - тип ошибки/исключения: E_USER_ERROR, E_USER_WARNING, 
//              E_USER_NOTICE, E_USER_DEPRECATED;
//   $div     - имя div-а для сообщения в режимах rvsMakeDiv,rvsDialogWindow. 
//              По умолчанию 'Ers'.

// Возвращаемое значение 
//
//   $Result=true, если сообщение сформировано без ошибок 

// Зарегистрированные ошибки/исключения
//   
//   define ("WrongTypeError", "Неверно указан тип ошибки");

/**
 * Функция MakeUserError выводит сообщение из разрабатываемого программного 
 * модуля при возникновении ошибочной ситуации. Информационное сообщение об 
 * этом выводится в одном из четырёх режимов:
 * 
 * в режиме $Mode=rvsCurrentPos просто выводится сообщение в 
 * текущей позиции сайта. Данный режим используется при тестировании модулей;
 * 
 * в режиме по умолчанию $Mode=rvsTriggerError вызывается 
 * исключение с пользовательской ошибкой через trigger_error($Message,$errtype), 
 * где $Message - текст сообщения, $errtype может быть одним из значений 
 * E_USER_ERROR, E_USER_WARNING, E_USER_NOTICE, E_USER_DEPRECATED. 
 * По умолчанию E_USER_ERROR;
 * 
 * в режиме $Mode=rvsMakeDiv предполагается, что ошибка произошла
 * в php-коде до разворачивания html-страницы и, в этом случае, формируется 
 * дополнительный div сообщения с id="Ers";
 * 
 * в режиме $Mode=rvsDialogWindow разворачивается сообщение в 
 * диалоговом окне с помощью JQueryUI. В этом случае на вызывающем сайте должны 
 * быть подключены модули jquery,jquery-ui,jquery-ui.css, например от Microsoft:
 * 
 * <link rel="stylesheet" type="text/css"
 *    href="https://ajax.aspnetcdn.com/ajax/jquery.ui/1.10.3/themes/ui-lightness/jquery-ui.css">
 *    <script
 *       src="https://ajax.aspnetcdn.com/ajax/jQuery/jquery-1.11.2.min.js">
 *    </script>
 *    <script
 *       src="https://ajax.aspnetcdn.com/ajax/jquery.ui/1.11.2/jquery-ui.min.js">
 *    </script>
 *    
 * Функция MakeUserError выделяет два вида ошибок (контроллируемые и 
 * неконтроллируемые) и определяет их следующим образом:
 *    а) ошибка является контроллируемой в случае, когда известно в каком месте 
 * сайта она может возникнуть и, таким образом, сообщение об ошибке можно 
 * вывести на экран по разметке сайта;
 *    б) в остальных случаях ошибка является неконтроллируемой и вывод сообщения
 * об ошибке выполняется на отдельной странице;
 *    в) по умолчанию функция генерирует неконтроллируемую ошибку/исключение:
 * trigger_error($Message,E_USER_ERROR), предполагая на верхнем уровне обработку
 * ошибки через сайт doortry.ru, где неконтроллируемая ошибка возникает на 
 * странице исключения с трассировкой его всплывания;
**/

// ****************************************************************************
// *       Развернуть сообщение в диалоговом окне  с помощью JQueryUI         *
// ****************************************************************************
function MakeMode2($Mess,$Prefix,$div)
{
   $title="Сообщение  [".$Prefix."]";
   echo '<div id="'.$div.'" title="'.$title.'">';
   echo $Mess;
   echo "</div>";
?>
<script>
   $(document).ready(function(){
      $('#<?php echo $div; ?>').dialog
      ({
         width: 600,
         position: 'left top',
         show: {effect:'slideDown'},
         hide: {effect:'explode', delay:250, duration:1000, easing:'easeInQuad'}
      });
   });
</script>
<?php
}
// ****************************************************************************
// *                    Cгенерировать ошибку/исключение или                   *
// *                  просто сформировать сообщение об ошибке                 *
// ****************************************************************************
function MakeUserError($Mess,$Prefix='TPhpPrown',$Mode=0,$errtype=E_USER_ERROR,$div='Ers')
{
   $Result=true;
   $Message='['.$Prefix.'] '.$Mess;
   if ($Mode==rvsCurrentPos)
   {
      echo $Message;
   } 
   else if ($Mode==rvsMakeDiv)
   {
      echo '<div id="'.$div.'">'.$Message.'</div>';
   } 
   elseif ($Mode==rvsDialogWindow)
   {
      MakeMode2($Mess,$Prefix,$div);
   } 
   else
   {
      // Выдаем исключение с сообщением об ошибке
      $Result=trigger_error($Message,$errtype);
      // Выдаем исключение, если неверно указан тип ошибки
      if ($Result=false)
      {
         trigger_error($Prefix.': '.WrongTypeError,$errtype);
      }   
   }
   return $Result; 
}
// ****************************************************** MakeUserError.php ***
