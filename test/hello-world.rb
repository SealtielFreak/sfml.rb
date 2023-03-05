require 'sfml'
include SFML

def random_color
  Array.new(3) { rand 255 } + [255]
end

def random_vec2(x=640, y=480)
  [rand(x), rand(y)]
end

class DrawableTest < Transformable
  include Drawable

  def initialize
    @circles = Array.new(32) { Circle.new rand 1..5 }
    @circles.each { |c| c.fill_color = random_color }
  end

  def draw(target, state)
    state.matrix = Transform.combine(state.matrix, self.matrix)
    @circles.each { |c| c.position = random_vec2 }
    @circles.each { |c| target.draw c, state }
  end
end

circles = Array.new(100) { Circle.new rand(5..25) }
transformable = Transformable.new
window = Window.new VideoMode.new(640, 480, 32), 'SFML'
event = Event.new
clock = Clock.new
test = DrawableTest.new
current = 0
dt = 1.0
color = random_color

window.frame_rate = 60
transformable.origin = [640/2, 480/2]
transformable.position = [640/2, 480/2]


circles.each do |c|
  c.position = random_vec2
  c.fill_color = random_color 
end

while window.is_open?
  while window.poll_event! event
    case event.type
    when 'closed'
      puts 'Goodbye!'
      window.close!
    when 'resized'
      puts "Resized: #{event.size}"
    when 'key-pressed'
      puts "Key pressed: #{event.key}"
    end

  end

  puts window.position.to_s
  
  if current > 15
    color = random_color
    current = 0
  end
  
  dt = clock.elapsed_time
  view = View.new

  current += 1

  window.clear color
  
  circles.each { |c| window.draw c }

  view.zoom 0.5 
  window.view = view 
  window.draw test
  
  window.view = window.default_view

  window.display

  clock.restart!
end
