<?php

/**
 * @file
 * Provides Entity metadata integration.
 */
 
/**
 * Extend the defaults.
 */
class FundingApplicationMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['label'] = array(
      'label' => t('Label'),
      'description' => t('The funding application label'),
      'getter callback' => 'entity_property_getter_method',
    );

    $properties['type'] = array(
      'type' => 'funding_application_type',
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer funding applications',
      'required' => TRUE,
      'description' => t('The funding application type.'),
    ) + $properties['type'];

    unset($properties['uid']);

    $properties['applicant'] = array(
      'label' => t("Applicant"),
      'type' => 'user',
      'description' => t("The applicant of the funding application."),
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_setter_method',
      'setter permission' => 'administer funding applications',
      'required' => TRUE,
      'schema field' => 'uid',
    );
    return $info;
  }
}
