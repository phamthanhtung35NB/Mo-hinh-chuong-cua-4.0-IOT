# Nha_Thong_Minh
## Cấu tạo của sản phẩm:
- Phần mô hình nhà được làm từ bìa làm mô hình (Formex).
- Và các linh kiện điện tử:
+ 1.Mạch đọc tín hiệu của thẻ từ.
+ 2.Động cơ Servo để đóng mở cửa.
+ 3.Mạch cảm biến ánh sáng.
+ 4.Cột đèn trong sân.
+ 5.Module Esp32 Camera dùng để giao tiếp với điện thoại và mạch Arduino R3 + chụp ảnh.
+ 6.Mạch Arduino R3 dùng để xử lý tín hiệu của mạch đọc thẻ từ, mạch cảm biến ánh sáng và các nút nhấn rồi điều khiển động cơ Servo đóng mở cửa.
	
- Phần mã nguồn (code) của module Esp32 Camera và mạch Arduino R3: https://github.com/phamthanhtung35NB/Mo-hinh-chuong-cua-4.0-IOT
## Tính sáng tạo của sản phẩm:
+ Khi có người bấm chuông cửa camera sẽ chụp ảnh người bấm rồi gửi về ứng dụng nhắn tin telegram trên điện thoại hay máy tính đều dùng được.
+ Có thể sử dụng điện thoại hoặc máy tính để mở của ở bất cứ đâu chỉ cần có kết nối internet và ở trong group chat của telegram.
+ Cửa còn có thể đóng-mở bằng thẻ từ với người bên ngoài và đóng-mở cổng bằng nút nhấn với người ở bên trong.
+ Khi vào trời tối mà mở cửa đèn sân sẽ tự động được bật sang và tự tắt khi cổng được đóng.
+ Chụp hình những bạn nhỏ hay trêu bấm chuông cửa của mọi nhà.
+ Ngoài ra chuông còn có thể bật đèn sân, chụp ảnh trước cổng từ xa.
## Nguyên lý làm việc:
- Để sử dụng trước hết cần kết nối sản phẩm với wifi ở đây em sẽ dùng điện thoại để phát wifi với tên wifi là: “iphone” và mật khẩu là “123456789”.
- Bên cạnh của có một nút chính là chuông cửa, khi ấn thì camera sẽ chụp hình và gửi về điện thoại. Chủ nhà có thể mở cửa từ xa để cho khách mà không cần xuống tận cổng, hoặc trong trường hợp không có ai ở nhà hay có người trong nhà về không mở được cổng như khi em bị quên thẻ từ (hoặc quên chìa khóa như trước đây).
- Nếu trời tối khi mở cửa đèn sân sẽ sáng và tự tắt khi đóng cổng.
- Nếu là người trong gia đình muốn mở hay khóa của có thể dùng 1 chiếc thẻ từ để chạm vào phần dưới camera hoặc sử dụng nút bấm ở trong sân(hoặc trong nhà tùy vào nơi lắp nút).
- Đây là 1 số câu lệnh để điều khiển chuông cửa từ xa:
/photo : chụp ảnh.
/open : để mở cửa.
/close : để khóa cửa.
/batden : bật đèn sân.
/tatden : tắt đèn sân.



chân dùng 

![Capture1](https://user-images.githubusercontent.com/81307877/222785058-d9d7853e-0be2-4574-b41e-40886cb839d7.PNG)

sơ đồ chân 

![ESP32-CAM-pinout](https://user-images.githubusercontent.com/81307877/222785064-d0e8ca8e-91f5-4849-9185-8c59fad4a0a3.png)

