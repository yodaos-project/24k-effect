module.exports = function () {
  print('render.js start')
  light.requestAnimationFrame(function () {
    light.render()
  }, 100)

  light.pixel(0, 255, 255, 255)
  while (true) {};
}
