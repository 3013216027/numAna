var offset = 10;
var width = window.innerWidth - offset;
var height = window.innerHeight - offset;

//console.log(width + ', ' + height);
var svg = d3.select('body').append('svg').attr('width', width).attr('height', height);
var generateSegment = () => {
  return svg.selectAll('polyline').data([0]).enter().append('polyline').attr('style', style);
};
var style = 'fill:white; stroke:red; stroke-width:2;';

var addSegment = function addSegment(sx, sy, tx, ty) {
  generateSegment().attr('points', function() {
    return '' + sx + ',' + sy + ' ' + tx + ',' + ty;
  })
}

addSegment(0, 0, width, height);