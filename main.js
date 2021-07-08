let table;

function preload()
{
  table = loadTable('https://celine10811020.github.io/Test/影集.csv', 'csv', 'header');
}

function setup()
{
  {
  noCanvas();
  createP('這是第一段文字');
  createP('這是第二段文字');
  createImg('NanoPutian.png', 'NanoPutian not found');

  createP('');
  var ele_0 = document.createElement("audio");
  ele_0.src = '歌曲串燒.mp3';
  ele_0.controls = true;
  ele_0.autoplay = true;
  ele_0.loop = true;
  document.body.appendChild(ele_0);

  createP('');
  var ele_1 = document.createElement("video");
  ele_1.src = '歌曲串燒.mp4';
  ele_1.controls = true;
  ele_1.loop = true;
  document.body.appendChild(ele_1);
  }

  {
  createP('');
  createCanvas(700, 570);
  searchStationInput = createInput();
  searchStationInput.position(30, 1190);
  searchStationInput.size(60);
  searchTotalInput = createInput();
  searchTotalInput.position(120, 1190);
  searchTotalInput.size(60);
  searchStationButton = createButton("搜尋網站");
  searchStationButton.position(30, 1220);
  searchStationButton.mouseClicked(searchStationResult);
  searchTotalButton = createButton("搜尋共幾集");
  searchTotalButton.position(120, 1220);
  searchTotalButton.mouseClicked(searchTotalResult);
  showTableButton = createButton("Show the table");
  showTableButton.position(400, 1220);
  showTableButton.mouseClicked(showTable);

  showTable();
  }

  {
  checkboxDate = createCheckbox('Date');
  checkboxDate.changed(checkeEventDate);
  checkboxDate.position(20, 1760);
  checkbox_1 = createCheckbox("January");
  checkbox_1.position(20, 1780);
  checkbox_1.hide();
  checkbox_2 = createCheckbox("Fabruary");
  checkbox_2.position(120, 1780);
  checkbox_2.hide();
  checkbox_3 = createCheckbox("March");
  checkbox_3.position(220, 1780);
  checkbox_3.hide();
  checkbox_4 = createCheckbox("Fabruary");
  checkbox_4.position(310, 1780);
  checkbox_4.hide();
  checkbox_5 = createCheckbox("May");
  checkbox_5.position(400, 1780);
  checkbox_5.hide();
  checkbox_6 = createCheckbox("June");
  checkbox_6.position(470, 1780);
  checkbox_6.hide();
  checkbox_7 = createCheckbox("July");
  checkbox_7.position(540, 1780);
  checkbox_7.hide();
  checkbox_8 = createCheckbox("August");
  checkbox_8.position(610, 1780);
  checkbox_8.hide();
  checkbox_9 = createCheckbox("September");
  checkbox_9.position(700, 1780);
  checkbox_9.hide();
  checkbox_10 = createCheckbox("October");
  checkbox_10.position(810, 1780);
  checkbox_10.hide();
  checkbox_11 = createCheckbox("November");
  checkbox_11.position(900, 1780);
  checkbox_11.hide();
  checkbox_12 = createCheckbox("December");
  checkbox_12.position(1000, 1780);
  checkbox_12.hide();
  checkboxSelect = createCheckbox("全選");
  checkboxSelect.position(1100, 1780);
  checkboxSelect.hide();
  checkboxSelect.changed(checkEventSelect);
  }
}

function draw()
{

}

function showTable()
{
  clear();

  for (let r=0; r<table.getRowCount(); r++)
  {
    for (let c=0; c<table.getColumnCount(); c++)
    {
      text(table.getString(r, c), 20+c*100, 70+r*20);
    }
  }
}

function searchStationResult()
{
  clear();

  let search = searchStationInput.value();

  // Get the row values using findRows()
  if (search != "")
  {
    // Find the results in the column
    let result = table.findRows(search, 'station');

    if (result.length > 0)
    {
      text("Result:", 20, 120);

      for(let i=0; i<result.length; i++)
      {
        for(let j=0; j<7; j++)
        {
          text(result[i].arr[j], 20+j*100, 140+i*20);
        }
      }
    }else
    {
      text("No Results Found", 20, 120);
    }
  }else
  {
    showTable();
  }

  searchStationInput.value("");
}

function searchTotalResult()
{
  clear();

  let search = searchTotalInput.value();

  if (search != "")
  {
    result = table.findRows(search, 'total');

    if (result.length > 0)
    {
      text("Result:", 20, 120);

      for(let i=0; i<result.length; i++)
      {
        for(let j=0; j<7; j++)
        {
          text(result[i].arr[j], 20+j*100, 140+i*20);
        }
      }
    }else
    {
      text("No Results Found", 20, 120);
    }
  }else
  {
    showTable();
  }

  searchTotalInput.value("");
}

function checkeEventDate()
{
  if(checkboxDate.checked())
  {
    checkbox_1.show();
    checkbox_2.show();
    checkbox_3.show();
    checkbox_4.show();
    checkbox_5.show();
    checkbox_6.show();
    checkbox_7.show();
    checkbox_8.show();
    checkbox_9.show();
    checkbox_10.show();
    checkbox_11.show();
    checkbox_12.show();
    checkboxSelect.show();
  }else
  {
    checkbox_1.hide();
    checkbox_2.hide();
    checkbox_3.hide();
    checkbox_4.hide();
    checkbox_5.hide();
    checkbox_6.hide();
    checkbox_7.hide();
    checkbox_8.hide();
    checkbox_9.hide();
    checkbox_10.hide();
    checkbox_11.hide();
    checkbox_12.hide();
    checkboxSelect.hide();
  }
}

function checkEventSelect()
{
  if(checkboxSelect.checked())
  {
    checkbox_1.checked(true);
    checkbox_2.checked(true);
    checkbox_3.checked(true);
    checkbox_4.checked(true);
    checkbox_5.checked(true);
    checkbox_6.checked(true);
    checkbox_7.checked(true);
    checkbox_8.checked(true);
    checkbox_9.checked(true);
    checkbox_10.checked(true);
    checkbox_11.checked(true);
    checkbox_12.checked(true);
  }else
  {
    checkbox_1.checked(false);
    checkbox_2.checked(false);
    checkbox_3.checked(false);
    checkbox_4.checked(false);
    checkbox_5.checked(false);
    checkbox_6.checked(false);
    checkbox_7.checked(false);
    checkbox_8.checked(false);
    checkbox_9.checked(false);
    checkbox_10.checked(false);
    checkbox_11.checked(false);
    checkbox_12.checked(false);
  }
}
