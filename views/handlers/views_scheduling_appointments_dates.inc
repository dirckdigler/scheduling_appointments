<?php

/**
 * My custom filter handler
 */
class views_scheduling_appoinments_dates extends views_handler_filter {

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  function value_form(&$form, &$form_state) {
    $form['dates'] = array(
      '#type'       => 'container',
      '#attributes' => array(
        'class' => array(
          drupal_html_class('akt-shed-dates'),
        ),
      ),
    );
    $form['dates']['date'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Date between'),
      '#default_value' => NULL,
    );
    $form['dates']['date_end'] = array(
      '#type'          => 'textfield',
      '#title'         => t('And'),
      '#default_value' => NULL,
    );

    return $form;
  }

  function exposed_form(&$form, &$form_state) {
    $form['dates'] = array(
      '#type'       => 'container',
      '#attributes' => array(
        'class' => array(
          drupal_html_class('akt-shed-dates'),
        ),
      ),
    );
    $form['dates']['date'] = array(
      '#type'          => 'date_popup',
      '#title'         => t('Date between'),
      '#default_value' => NULL,
      '#date_format'   => 'd-m-Y',
    );
    $form['dates']['date_end'] = array(
      '#type'          => 'date_popup',
      '#title'         => t('And'),
      '#default_value' => NULL,
      '#date_format'   => 'd-m-Y',
    );
  }

  function query() {
    if (isset($this->view->exposed_data['date']) && !empty($this->view->exposed_data['date']) && ($this->view->exposed_data['date'] != '' || $this->view->exposed_data['date'] != 'All')) {
      $value = strtotime($this->view->exposed_data['date']);
      $value_end = ($this->view->exposed_input['date_end']['date']) ? (strtotime($this->view->exposed_input['date_end']['date']) + 86400) : ($value + 86400);
      $this->ensure_my_table();
      $table = 'scheduling_appointments';
      $this->query->add_where(
        $this->options['group'],
        db_and()
          ->condition($table . '.date', $value, '>=')
      );

      $this->query->add_where(
        $this->options['group'],
        db_and()
          ->condition($table . '.date', $value_end, '<=')
      );
    }
  }
}
