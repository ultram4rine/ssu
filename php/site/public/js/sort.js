$("th").click(function () {
  $("th").children().removeClass("fa-sort-up");
  $("th").children().removeClass("fa-sort-down");
  $("th").children().addClass("fa-sort");

  $(this).children().removeClass("fa-sort");

  var table = $(this).parents("table").eq(0);
  var rows = table
    .find("tr:gt(0)")
    .toArray()
    .sort(comparer($(this).index()));
  this.asc = !this.asc;

  $(this).children().removeClass("fa-sort-down");
  $(this).children().addClass("fa-sort-up");
  if (!this.asc) {
    $(this).children().removeClass("fa-sort-up");
    $(this).children().addClass("fa-sort-down");
    rows = rows.reverse();
  }
  for (var i = 0; i < rows.length; i++) {
    table.append(rows[i]);
  }
});

function comparer(index) {
  return function (a, b) {
    var valA = getCellValue(a, index),
      valB = getCellValue(b, index);
    return $.isNumeric(valA) && $.isNumeric(valB)
      ? valA - valB
      : valA.toString().localeCompare(valB);
  };
}

function getCellValue(row, index) {
  return $(row).children("td").eq(index).text();
}
