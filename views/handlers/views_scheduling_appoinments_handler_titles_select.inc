<?php

/**
 * My custom filter handler
 */
class views_scheduling_appoinments_handler_titles_select extends views_handler_filter {
  /*
  * Declaración de elementos del formulario de administración
  */
  function option_definition() {
    $options = parent::option_definition();
    $options['id_center_services'] = array('default' => FALSE, 'bool' => TRUE);

    return $options;
  }

  /*
    * Formulario de la administración, en option_definition declaramos los elementos del formulario para que se puedan guardar sus valores
    */
  function options_form(&$form, &$form_state) {
    //array con las opciones
    $query_centers = new EntityFieldQuery();
    $result = $query_centers->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'service_centers')
      ->propertyCondition('status', 1)
      ->execute();

    $nodes = node_load_multiple(array_keys($result['node']));
    $options = array();

    foreach ($nodes as $servicesCenter) {
      $options[$servicesCenter->nid] = $servicesCenter->title;
    }

    $form['id_center_services'] = array(
      '#type'          => 'select',
      '#options'       => $options,
      '#default_value' => $this->options['id_center_services'],
    );
    parent::options_form($form, $form_state);
  }


  /*
    * formulario expuesto
    */
  function exposed_form(&$form, &$form_state) {
    //array con las opciones
    $query_centers = new EntityFieldQuery();
    $result = $query_centers->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'service_centers')
      ->propertyCondition('status', 1)
      ->execute();

    $nodes = node_load_multiple(array_keys($result['node']));
    $options = array();

    $options['All'] = '-Cualquiera-';
    foreach ($nodes as $servicesCenter) {
      $options[$servicesCenter->nid] = $servicesCenter->title;
    }

    $form['id_center_services'] = array(
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
      $value = $this->options['id_center_services'];
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

    if (isset($value)) {

      $this->query->add_where(
        $this->options['Appointments'],
        db_and()
          ->condition($table . '.id_center_services', $value, '=')
      );
    }

  }


}
