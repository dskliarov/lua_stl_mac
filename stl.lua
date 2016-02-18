-- stl.lua
io.write("Executing demo script ", _VERSION, "\n");
-- FB1 logic
out1 = get_value("FB1.OUT1")
in1 = get_value("FB1.IN1")
in2 = get_value("FB1.IN2")
if(out1 > 0) then
    set_value("FB1.IN3", out1)
else
    set_value("FB1.IN3", 4)
end
if(in1 == 0) then set_value("FB1.IN1",15) end
if(in2 == 0) then set_value("FB1.IN2",35) end
in1_1 = get_value("FB1.IN1")
in1_2 = get_value("FB1.IN2")
in3 = get_value("FB1.IN3")
out2 = in1_1 + 10*in1_2 + in3/2
set_value("FB1.OUT1",out2)
-- FB2 logic
set_value("FB2.IN1",out2)
set_value("FB2.IN1",out2/10 + in3/12) 
set_value("FB2.IN2",in3/4)
in2_1 = get_value("FB2.IN1")
in2_2 = get_value("FB2.IN2")
out2_1 = ((in2_1/5 + in2_2/3) * 25)
set_value("FB1.OUT1",(in1/3 + out2_1*5 + in3*7 - in2))
set_value("FB1.OUT2",(in1/3 + out2_1*9 + in3*2 - in2/5))
set_value("FB2.OUT1",out2_1)
set_value("FB1.OUT3",out2_1/4)
set_value("FB2.OUT2",out2_1/5)




