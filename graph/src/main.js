var offset = 20;
var width = window.innerWidth - offset * 2;
var height = window.innerHeight - offset * 2;

//console.log(width + ', ' + height);
var body = d3.select('body');
var svg = body.append('svg').attr('width', width).attr('height', height);
var generateSegment = function() {
  return svg.append('line').attr('style', style);
};
var style = 'fill:white; stroke:red; stroke-width:2;';

var off = function(x) {
  return x + offset;
};

var addSegment = function(sx, sy, tx, ty) {
  generateSegment().attr('x1', off(sx)).attr('y1', off(sy))
  .attr('x2', off(tx)).attr('y2', off(ty));
};

var eps = 0.01;
var addFunction = function (left, right, fun) {
  var queue = [];
  var square = [1000007, 1000007, 0, 0];
  for (var i = left; i < right; i += eps) {
    queue.push(fun(i));
    if (i < square[0]) square[0] = i;
    if (i > square[2]) square[2] = i;
    if (fun(i) < square[1]) square[1] = fun(i);
    if (fun(i) > square[3]) square[3] = fun(i);
  }
  var times = Math.min(width / square[2], height / square[3]);
  console.log(times);
  queue[0] *= times;
  for (var i = left + eps, j = 1; i < right; i += eps) {
    queue[j] *= times;
    //addSegment(i - eps, queue[j - 1], i, queue[j]);
  }
};

/**
 * |
 * |
 * |
 * |
 * |
 * |
 * |
 * |
 * |
 * |____________________________________________________
 */
console.log('0, ' + height + ' -> ' + width + ', ' + height);
addSegment(0, 0, width, height);
addSegment(0, height, width, height);
addSegment(0, height, 0, 0);
addFunction(0, 20, function(x) {
  //console.log('add ' + x + ',' + x * x);
  return x * x;
});