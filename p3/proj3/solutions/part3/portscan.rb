lines = `grep " > " trace.txt`.each_line

packets = {}

lines.each do |line|
  ips = line.strip.split(':').first
  # puts line, ips
  origin, host = ips.split(' > ').map { |s| s.split('.') }

  next if origin.nil? || host.nil?

  origin_port = origin.pop.to_i
  origin_ip = origin.join('.')

  host_port = host.pop.to_i
  host_ip = host.join('.')

  packets[[origin_ip, host_ip]] ||= {}
  packets[[origin_ip, host_ip]][host_port] ||= 0
  packets[[origin_ip, host_ip]][host_port] += 1

  packets[[origin_ip, host_ip]][:count] ||= 0
  packets[[origin_ip, host_ip]][:count] += 1

  # puts line
  # puts "#{origin_ip}:#{origin_port} => #{host_ip}:#{host_port}"
  # exit 0
end

sorted = packets.to_a.sort_by { |k,v| v[:count] }
puts sorted

scan_origin, scan_host = ['10.30.1.65', '10.30.5.234']
scan_ports = packets[[scan_origin, scan_host]] # by inspection
scan_count = scan_ports.delete(:count)
ports = scan_ports.keys.map(&:to_i).sort

puts "Portscan origin: #{scan_origin}"
puts "Portscan host: #{scan_host}"
puts "Portscan packet count: #{scan_count}"
puts "Portscan ports: #{ports.first} through #{ports.last}"
