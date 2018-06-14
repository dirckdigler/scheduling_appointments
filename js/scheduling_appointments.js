(function ($) {

  Drupal.scheduling_appointments = Drupal.scheduling_appointments || {};
  Drupal.behaviors.schedulingAppointments = {
    attach: function (context, settings) {

      $('body').once(function () {
        var date_texfiel = $('.edit-date').val();
        $.datepicker.regional['es'] = {
          closeText: 'Cerrar',
          prevText: '&#x3c;Ant',
          nextText: 'Sig&#x3e;',
          currentText: 'Hoy',
          monthNames: ['Enero', 'Febrero', 'Marzo', 'Abril', 'Mayo', 'Junio', 'Julio', 'Agosto', 'Septiembre', 'Octubre', 'Noviembre', 'Diciembre'],
          monthNamesShort: ['Ene', 'Feb', 'Mar', 'Abr', 'May', 'Jun', 'Jul', 'Ago', 'Sep', 'Oct', 'Nov', 'Dic'],
          dayNames: ['Domingo', 'Lunes', 'Martes', 'Mi&eacute;rcoles', 'Jueves', 'Viernes', 'S&aacute;bado'],
          dayNamesShort: ['Dom', 'Lun', 'Mar', 'Mi&eacute;', 'Juv', 'Vie', 'Sab'],
          dayNamesMin: ['Dom', 'Lun', 'Mar', 'Mie', 'Jue', 'Vie', 'S&aacute;b'],
          weekHeader: 'Sm',
          dateFormat: 'mm/dd/yy',
          firstDay: 1,
          isRTL: false,
          showMonthAfterYear: false,
          yearSuffix: ''
        };
        $.datepicker.setDefaults($.datepicker.regional['es']);
      });

      $('.state_date').change(function (e) {
        window.location.href = $(e.target).val();
      });

      var disable_days = [],
        i,
        information = [];

      $('.hours').html('<li class="no-hours"> Selecciona el horario de tu cita</li>');

      try {

        for (i = 0; i < Drupal.settings.scheduling_appointments.unable_days.length; ++i) {
          disable_days[i] = Drupal.settings.scheduling_appointments.unable_days[i];
        }

        for (i = 0; i < Drupal.settings.scheduling_appointments.information.length; ++i) {
          information[i] = Drupal.settings.scheduling_appointments.information[i];
        }

      } catch (err) {
      }

      $("#edit-date").datepicker({dateFormat: 'mm-dd-yy',});

      var date = $("input.edit-date").val();
      var hour = $("input.edit-hour").val();
      var isMobile = {
        Android: function() {
          return navigator.userAgent.match(/Android/i);
        },
        BlackBerry: function() {
          return navigator.userAgent.match(/BlackBerry/i);
        },
        iOS: function() {
          return navigator.userAgent.match(/iPhone|iPad|iPod/i);
        },
        Opera: function() {
          return navigator.userAgent.match(/Opera Mini/i);
        },
        Windows: function() {
          return navigator.userAgent.match(/IEMobile/i);
        },
        any: function() {
          return (isMobile.Android() || isMobile.BlackBerry() || isMobile.iOS() || isMobile.Opera() || isMobile.Windows());
        }
      };

      /*if (date) {
        $(".hourscontainer h2").html(date);
        $.ajax({
          type: 'POST',
          url: Drupal.settings.basePath + 'pide_tu_cita/horario',
          dataType: 'json',
          success: function (data) {
            $('.hours').empty();
            $.each(data, function (i) {
              $('.hours').append("<li class='hourscroll'><input type='radio' name='hour' id=" + data[i] + "><span>" + data[i] + "</span></li>");
            });

            //Eleccion horario
            $("input[name='hour']").click(function () {
              var hora = $(this).siblings("span").text();
              if ($(this).is(':checked')) {
                $("input.edit-hour").val(hora);
              }
            });

            $('input:radio[id=' + hour + ']').attr('checked', true);

          },
          data: 'dt=' + date + '&dp=' + information[0] + '&ct=' + information[1] + '&cs=' + information[2] + '&st=' + information[3],
        });
      }*/


      $("#calendario").datepicker({
        minDate: '1d',
        maxDate: '180d',
        dateFormat: 'mm-dd-yy',
        defaultDate: date,
        //setDate: '06/06/2009',
        beforeShowDay: function (date) {
          var formatDate = jQuery.datepicker.formatDate('mm-dd-yy', date);

          return [$.inArray(formatDate, disable_days) == -1];
        },
        inline: true,
        onSelect: function (dateText, inst) {
          var date = $(this).datepicker('getDate'),
            day = date.getDate(),
            month = date.getMonth() + 1,
            year = date.getFullYear(),
            monthNames = ['Enero', 'Febrero', 'Marzo', 'Abril', 'Mayo', 'Junio', 'Julio', 'Agosto', 'Septiembre', 'Octubre', 'Noviembre', 'Diciembre'];
          if (month < 10) {
            month = '0' + month;
          }

          var fulldate = (day + '-' + month + '-' + year);

          $("input.edit-date").val(fulldate);
          if(isMobile.any()) {
            $(".hourscontainer h2").html('DÍA - ' + day + ' de ' + monthNames[parseInt(month) - 1] + ' ' + year);
          } else {
            $(".hourscontainer h2").html(day + ' de ' + monthNames[parseInt(month) - 1] + ' ' + year);
          }

          $.ajax({
            type: 'POST',
            url: Drupal.settings.basePath + 'pide_tu_cita/horario',
            dataType: 'json',
            success: function (data) {
              $('.hours').empty();
              $('.hours-movil').empty();
              if(isMobile.any()) {
                $('.hours-movil').append("<li class='hourscroll'><select name='hour' id='select-time'></select></li>");
                $('.hours-movil select').append("<option value='audi' selected>Selecciona la hora</option>");
                $('#select-time').fadeIn(100000, function() {
                  $('#select-time').css({
                    border: 'solid 2px red',
                  });
                });
                $('#select-time').animate({border: 'solid 2px red'});
              }
              $.each(data, function (i) {
                if(isMobile.any()) {
                  $('.hours-movil select').append("<option>" + data[i] + "</option>");
                } else {
                  $('.hours').append("<li class='hourscroll'><input type='radio' name='hour' id=" + data[i] + "><span>" + data[i] + "</span></li>");
                }
              });

              //Elección horario V. web
              $("input[name='hour']").click(function () {
                var hora = $(this).siblings("span").text();
                if ($(this).is(':checked')) {
                  $("input.edit-hour").val(hora);
                }
              });

              //Elección horario V. mobile
              $('select[name="hour"]').on('change', function (e) {
                var optionSelected = $("option:selected", this);
                var hourMovil = this.value;
                $("input.edit-hour").val(hourMovil);
              });

            },
            error: function (jqXHR, exception) {
              //Write some code
            },
            data: 'dt=' + fulldate + '&dp=' + information[0] + '&ct=' + information[1] + '&cs=' + information[2] + '&st=' + information[3],
          });
        }
      });

      if(isMobile.any()) {
        //Show and hide driving license step
        if (!$('.link_chassis').data('seAsignoClick')) {
          var selectImg = $('#popup-content-chassis img');
          selectImg.hide();
          $('.link_chassis').on('click', function (event) {
            selectImg.slideUp();
            var heightImg = $('#popup-content-chassis img').height();
            $('.highlight').css({'margin-top': heightImg + 62});

            if (selectImg.css('display') == 'none') {
              selectImg.slideDown("slow");
              $('#back-arrow').toggleClass("highlight");
              $('.highlight').css({'margin-top': heightImg + 62});
            } else {
              $('#back-arrow').css({'margin-top': 100});
            }
          }).data('seAsignoClick', true);
        }
        //Add button to accept the confirmation scheduling appointment
        if ($('#modalContent').length) {
          if (!$('#modalContent').data('existData')) {
            $('.page-pide-tu-cita #scheduling-appointments-form').css({display : 'none'});
            $('.slide').css({display : 'none'});
            $('.page-pide-tu-cita .slide').css({'bottom' : '-224px'});
            $('.page-pide-tu-cita #footer').css({'top' : '193px'});
            $('#modalContent').load(function () {
              $('#modalContent').after('<div class="wrapper-edit-accept"><a id="edit-accept" href="envio-pide-tu-cita">ACEPTAR</a></div>');
            }).data('existData', true);
          } else {
            $('#modalContent').after('<div class="wrapper-edit-accept"><a id="edit-accept" href="envio-pide-tu-cita">ACEPTAR</a></div>');
          }
        }
      }
    }
  };

})(jQuery)
