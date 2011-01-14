<?php
// $Id: webform_handler_field_node_link_edit.inc,v 1.1.2.2 2010/09/11 02:18:53 quicksketch Exp $
/**
 * Field handler to present a link node edit.
 */
class webform_handler_field_node_link_edit extends views_handler_field_node_link {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
    $this->additional_fields['type'] = 'type';
    $this->additional_fields['format'] = array('table' => 'node_revisions', 'field' => 'format');
  }

  function render($values) {
    // ensure user has access to edit this node.
    $node = new stdClass();
    $node->nid = $values->{$this->aliases['nid']};
    $node->uid = $values->{$this->aliases['uid']};
    $node->type = $values->{$this->aliases['type']};
    $node->format = $values->{$this->aliases['format']};
    $node->status = 1; // unpublished nodes ignore access control
    if (!node_access('update', $node)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit webform');
    return l($text, "node/$node->nid/webform");
  }
}
