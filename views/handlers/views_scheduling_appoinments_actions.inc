<?php
/**
 * @file
 * Definition of actions handler.
 */

/**
 * Actions
 */
class SchedulingAppointmentsActionss extends views_handler_field {
  /**
   * Add some required fields needed on render().
   */
  function construct() {
    parent::construct();

  }

  /**
   * Loads additional fields.
   */
  function query() {
    $this->ensure_my_table();
  }

  /**
   * Default options form.
   */
  function option_definition() {
    $options = parent::option_definition();

    return $options;
  }

  /**
   * Creates the form item for the options added.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  /**
   * Renders the field handler.
   */
  function render($values) {
    if (isset($values->id_appointment)) {
      $state = isset($values->scheduling_appointments_state) ? $values->scheduling_appointments_state : NULL;

      return render(drupal_get_form('_scheduling_appointments_actions_form', $values->id_appointment, $state));
    }
  }
}
