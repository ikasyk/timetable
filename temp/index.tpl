<!doctype html>
<html>
<head>
<meta charset="UTF-8">
<title>iRozklad | Розклад занять станом на {{export_date}}</title>
<style>
* { margin: 0; padding: 0; }

body {
  font-family: Gotham, "Helvetica Neue", Helvetica, Arial, sans-serif;
  font-size: 12px;
  background: #FFF;
}

#page-wrap {
  padding: 15px;
}

#export-date {
  color: #a1a1a1;
}

table {
  width: 100%;
  border-collapse: collapse;
}

.week-table, .week-table td, .week-table th {
  border: 1px solid #eaeaea;
  border-width: 1px 0px 0px 1px;
}

.week-table {
  margin-bottom: 10px;
}

.week-table caption {
  font-size: 17px;
  font-weight: bold;
  padding: 5px 0px 10px;
  color: #2b6084;
  font-style: italic;
}

.week-table td, .week-table th {
  border-width: 0px 1px 1px 0px;
  width: 16.67%;
  padding: 5px;
}

.week-table th {
  text-align: center;
  background: #fafbfc;
}

.week-table figure {
  height: 80px;
  text-align: center;
}

.week-table figcaption {
  font-size: 13px;
}

.week-table div {
  line-height: 20px;
}
</style>
</head>

<body>

<div id="page-wrap">
    <div id="export-date">Розклад станом на {{export_date}}</div>

{{#week_table}}
    <table class="week-table">
        <caption>Тиждень {{week_id}}</caption>
        <tr>
            <th>Понеділок</th>
            <th>Вівторок</th>
            <th>Середа</th>
            <th>Четвер</th>
            <th>П'ятниця</th>
            <th>Субота</th>
        </tr>
        {{#week_row}}
        <tr>
          {{#row_order}}
          <td>
            {{#order_content}}
            <figure><figcaption><b>{{subject}}</b> <i>{{type}}</i></figcaption><wrap><div>{{teacher}}</div><div>{{classroom}}</div></wrap></figure>
            {{/order_content}}
          </td>
          {{/row_order}}
        </tr>
        {{/week_row}}
    </table>
{{/week_table}}

</div>

</body>
</html>
