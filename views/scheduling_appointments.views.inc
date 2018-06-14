<?php
/**
 * @file
 * VIews data file.
 */

/**
 * Implements hook_views_data().
 */
function scheduling_appointments_views_data() {

  $data['motorcycle_owner'] = array(
    'table'                => array(
      'base'  => array(
        'field' => 'identification_owner',
        'title' => 'Motorcycle owner',
        'help'  => 'scheduling appointments info; InnoDB free: 2582528 kB',
      ),
      'group' => 'Motorcycle owner',
    ),
    'identification_owner' => array(
      'title' => 'Id del propietario',
      'help'  => 'The primary identifier for a appointment.',
      'field' => array(
        'handler'        => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
    ),
    'name_owner'           => array(
      'title' => 'Nombres',
      'help'  => 'Center services',
      'field' => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
    ),
    'last_name_owner'      => array(
      'title' => 'Apellidos',
      'help'  => 'Center services',
      'field' => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
    ),
    'address_owner'        => array(
      'title' => 'Dirección',
      'help'  => 'Center services',
      'field' => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
    ),
    'date_born_owner'      => array(
      'title' => 'Fecha de nacimiento',
      'help'  => 'Center services',
      'field' => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
    ),
    'phone_owner'          => array(
      'title' => 'Telefono',
      'help'  => 'Center services',
      'field' => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
    ),
    'mobile_phone'         => array(
      'title' => 'Telefono Movil',
      'help'  => 'Center services',
      'field' => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
    ),
    'email_owner'          => array(
      'title' => 'Email',
      'help'  => 'Center services',
      'field' => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
    ),
  );


  $data['scheduling_appointments'] = array(
    'table'             => array(
      'base'  => array(
        'field' => 'id_appointment',
        'title' => 'Appointments',
        'help'  => 'scheduling appointments info; InnoDB free: 2582528 kB',
      ),
      'group' => 'Appointments',
      'join'  => array(
        'motorcycle_owner' => array(
          'left_field' => 'identification_owner',
          'field'      => 'identification_owner',
        ),
      ),
    ),
    'id_appointment'    => array(
      'title' => 'Id de cita',
      'help'  => 'The primary identifier for a appointment.',
      'field' => array(
        'handler'        => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
    ),
    'reservation_code'  => array(
      'title' => 'Codigo de reservación',
      'help'  => 'The primary code identifier for a date.',
      'field' => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
    ),
    'tid_department'    => array(
      'title'        => 'Departamento',
      'help'         => 'Center services',
      'field'        => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
        'base'       => 'taxonomy_term_data',
        'base field' => 'tid',
        'handler'    => 'views_handler_relationship',
        'label'      => 'Related department',
        'title'      => 'Related department',
        'help'       => 'Related department info',
      ),
    ),
    'tid_city'          => array(
      'title'        => 'Ciudad',
      'help'         => 'Center services',
      'field'        => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
        'base'       => 'taxonomy_term_data',
        'base field' => 'tid',
        'handler'    => 'views_handler_relationship',
        'label'      => 'Related city',
        'title'      => 'Related city',
        'help'       => 'Related city info',
      ),
    ),
    'tid_type_services' => array(
      'title'        => 'Tipo de cita',
      'help'         => 'Center services',
      'field'        => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter'       => array(
        'handler' => 'views_handler_filter_term_node_tid',
      ),
      'relationship' => array(
        'base'       => 'taxonomy_term_data',
        'base field' => 'tid',
        'handler'    => 'views_handler_relationship',
        'label'      => 'Related type services',
        'title'      => 'Related type services',
        'help'       => 'Related type services info',
      ),
    ),

    'mileage'            => array(
      'title' => 'Kilometraje',
      'help'  => 'Center services',
      'field' => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
    ),
    'comments'           => array(
      'title' => 'Comentarios',
      'help'  => 'comentarios',
      'field' => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
    ),
    'id_center_services' => array(
      'title'        => 'Id del Centro de Servicios',
      'help'         => 'Id Center services',
      'field'        => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter'       => array(
        'handler' => 'views_scheduling_appoinments_handler_titles_select',
      ),
      'relationship' => array(
        'base'       => 'node',
        'base field' => 'nid',
        'handler'    => 'views_handler_relationship',
        'label'      => 'Related node',
        'title'      => 'Related node',
        'help'       => 'Related node info',
      ),
      'argument'     => array(
        'handler' => 'views_handler_argument_string',
      ),
    ),

    'date' => array(
      'title'  => 'Date',
      'help'   => 'Center services',
      'field'  => array(
        'handler'        => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_scheduling_appoinments_dates',
      ),
      'sort'   => array(
        'handler' => 'views_handler_sort',
      ),
    ),

    'chasis'               => array(
      'title' => 'Chasis',
      'help'  => 'Center services',
      'field' => array(
        'handler' => 'views_handler_field',
      ),
    ),
    'plate'                => array(
      'title' => 'Plate',
      'help'  => 'Center services',
      'field' => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
    ),
    'identification_owner' => array(
      'title'        => 'Identification Owner',
      'help'         => 'Center services',
      'field'        => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'relationship' => array(
        'base'       => 'motorcycle_owner',
        'base field' => 'identification_owner',
        'handler'    => 'views_handler_relationship',
        'label'      => 'Related owner',
        'title'      => 'Related owner',
        'help'       => 'Related owner info',
      ),
    ),

    'state' => array(
      'title'  => 'Estado',
      'help'   => 'Center services',
      'field'  => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    ),

    'uid' => array(
      'title'  => 'Id user',
      'help'   => 'Id user scheduling',
      'field'  => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_name_user',
      ),

      'relationship' => array(
        'base'       => 'users',
        'base field' => 'uid',
        'handler'    => 'views_handler_relationship',
        'label'      => 'Related users',
        'title'      => 'Related users',
        'help'       => 'Related users info',
      ),
    ),

    'site' => array(
      'title'  => t('Site'),
      'help'   => t('Site'),
      'field'  => array(
        'handler'        => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    ),

    'created'    => array(
      'title'  => t('Date created'),
      'help'   => 'Date when the scheduling was created',
      'field'  => array(
        'handler'        => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
      'sort'   => array(
        'handler' => 'views_handler_sort_date',
      ),
    ),
    'sh_actions' => array(
      'title' => t('Actions'),
      'help'  => t('Actions'),
      'field' => array(
        'handler' => 'SchedulingAppointmentsActionss',
      ),
    ),

  );

  return $data;
}
