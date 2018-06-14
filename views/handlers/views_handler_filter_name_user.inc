<?php

/**
 * My custom filter handler
 */
class views_handler_filter_name_user extends views_handler_filter {
  /*
  * Declaración de elementos del formulario de administración
  */


  function option_definition() {
    $options = parent::option_definition();
    $options['uid'] = array('default' => FALSE, 'bool' => TRUE);

    return $options;
  }

  /*
    * Formulario de la administración, en option_definition declaramos los elementos del formulario para que se puedan guardar sus valores
    */
  function options_form(&$form, &$form_state) {
    //array con las opciones
    /*$query_users = new EntityFieldQuery();
        $result = $query_users->entityCondition('name_user', 'dates')
          ->propertyCondition('status', 1)
          ->execute();

      $dates = node_load_multiple(array_keys($result['dates']));*/
    $query = db_select('users', 'u')
      ->fields('u', array('uid', 'name'));
    $query->innerJoin('scheduling_appointments', 's', 's.uid = u.uid');
    $query->distinct();
    $result = $query->execute();

    $options = array();
    $options['All'] = '-Cualquiera-';

    while ($name = $result->fetchAssoc()) {
      $options[$name['uid']] = $name['name'];
      if ($name['uid'] == 0) {
        $options[$name['uid']] = 'Anonimo';
      }
    }


    $form['uid'] = array(
      '#type'          => 'select',
      '#options'       => $options,
      '#default_value' => $this->options['uid'],
    );
    parent::options_form($form, $form_state);
  }


  /*
    * formulario expuesto
    */
  function exposed_form(&$form, &$form_state) {
    //array con las opciones


    $query = db_select('users', 'u')
      ->fields('u', array('uid', 'name'));
    $query->innerJoin('scheduling_appointments', 's', 's.uid = u.uid');
    $query->distinct();
    $result = $query->execute();

    $options = array();
    $options['All'] = '-Cualquiera-';

    while ($name = $result->fetchAssoc()) {
      $options[$name['uid']] = $name['name'];
      if ($name['uid'] == 0) {
        $options[$name['uid']] = 'Anonimo';
      }
    }

    $form['uid'] = array(
      '#type'    => 'select',
      '#options' => $options,
    );
  }

  function exposed_validate(&$form, &$form_state) {

    if (empty($this->options['exposed'])) {
      return;
    }

    if (empty($this->options['expose']['identifier'])) {
      return;
    }

    $identifier = $this->options['expose']['identifier'];
    $input = $form_state['values'][$identifier];

    $this->validated_exposed_input = drupal_explode_tags($input);

  }

  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }
  }


  // the query method is responsible for actually running our exposed filter
  function query() {
    // Don't filter if we're exposed and the checkbox isn't selected.

    if ((!empty($this->options['exposed'])) && empty($this->value)) {
      return;
    }
    if (!$this->options['exposed']) {
      $value = $this->options['uid'];
    }
    else {
      $value = $this->validated_exposed_input[0];
    }


    $this->ensure_my_table();


    $table = 'scheduling_appointments';
    //$field1 = $this->query->add_field($table, 'nid');
    //$field2 = $this->query->add_field($table, 'title');


    //$field1 = $table . '.nid';
    //$field2 = $table . '.title';
    if ($value != '') {
      $this->query->add_where(
        $this->options['group'],
        db_and()
          ->condition($table . '.uid', $value, '=')
      );
    }
  }


}






