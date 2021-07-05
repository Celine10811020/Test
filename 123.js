let table;

function preload()
{
  table = loadTable('影集.csv', 'csv', 'header');
}

function setup()
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

  print(table.getRowCount() + ' total rows in table');
  print(table.getColumnCount() + ' total columns in table');
  print(table.getColumn('name'));
  for (let r = 0; r < table.getRowCount(); r++)
  {
    for (let c = 0; c < table.getColumnCount(); c++)
    {
      print(table.getString(r, c));
    }
  }
}

function draw(){
}
