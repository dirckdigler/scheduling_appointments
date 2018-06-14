<?php

/**
 * My custom filter handler
 */
class views_scheduling_appoinments_hour extends views_handler_filter {

  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

  }

  function value_form(&$form, &$form_state) {

    $form['hour'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Hour'),
      '#default_value' => NULL,
    );

    return $form;
  }

  function exposed_form(&$form, &$form_state) {

    $form['hour'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Hour'),
      '#default_value' => NULL,
    );


  }

  function query() {

    $value = $this->value['0'];
    $hour_minutes = date('H:i');
    $this->ensure_my_table();
    $table = 'scheduling_appointments';
    $this->query->add_where(
      $this->options['group'],
      db_and()
        ->condition(date('H:i', $table . '.date'), $value, '>=')
    );
  }


}
