# Tên game: Ping Pong
Thư viện sử dụng: STL và SDL2

## Gameplay:
- 2 người chơi: Người bên trái điều khiển bằng bằng nút W/S, người bên phải điều khiển bằng mũi tên lên xuống
- Mỗi trò chơi kéo dài cho đến khi một trong hai người chơi nhận được điểm thứ 10.
- Cả hai pad đều được điều khiển bởi người chơi.
- Vận tốc bóng được tăng lên sau mỗi lần đánh bằng mái chèo.
- Vận tốc bóng không vượt quá vận tốc tối đa được xác định trước.
- Chuyển động của quả bóng đang bị dừng lại trong 30 ticks sau mỗi lần đặt lại.
- Hướng bóng được chọn ngẫu nhiên từ bốn hướng khác nhau sau mỗi lần đặt lại.
- Pad được trả về vị trí mặc định sau mỗi lần đặt lại.

## Các tính năng khác:
- Background, ảnh cho pad và bóng
- Nhạc nền, âm thanh va chạm

### Về Scene
Game được chia là những scene sau:
1. welcome_scene
2. court_scene
3. endgame_scene
Chuyển scene:
- 1 đến 2: khi ấn nút bắt đầu
- 2 đến 3: khi 1 trong 2 người chơi chiến thắng
- 3 đến 1: khi ấn nút bắt đầu lần nữa



