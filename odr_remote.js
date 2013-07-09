Drupal.ajax.prototype.commands.odrUpdateKeys = function(ajax, response, status)
{
  var selector = response.data.selector;
  var val = response.data.val;
  jQuery(selector).val(val);
};