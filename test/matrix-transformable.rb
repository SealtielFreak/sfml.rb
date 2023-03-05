require 'sfml'
include SFML

def random_vec2(x, y)
  [rand(-x..x), rand(-y..y)]
end

transformable = Transformable.new

1000.times do
  state = RenderState.new
  
  1000.times do
    transformable.move random_vec2(100, 100)
    transformable.rotate rand(-90..90)

    state.matrix = transformable.matrix
    
    # puts "Transform position: #{transformable.position}"
    # puts "Transform angle: #{transformable.angle}"
  end

  puts "State's matrix: #{state.matrix}"

  sleep 0.0025
end

puts "Ok!"
