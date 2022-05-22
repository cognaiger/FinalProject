# THE ADVENTURERS

## Hướng dẫn cài đặt 
Lưu ý: Cách cài đặt này được thực hiện trên vscode, máy 64bit
1. Clone repository này xuống máy tính 
2. Download thư viện, các file cần thiết khác ở đây https://drive.google.com/drive/folders/1ogK7Zw4ZuO2cRvWGX7L-hNIJXjqY2izQ?usp=sharing
3. Trong file Makefile các bạn chú ý tùy chỉnh đường dẫn đến 'SDL2-2.0.20\x86_64-w64-mingw32\include' và 'SDL2-2.0.20\x86_64-w64-mingw32\lib' tùy theo đường dẫn ở máy bạn
4. Sau khi xong hết, để chạy chương trình các bạn gõ vào terminal trong vscode 'mingw32-make'
5. Chạy file main.exe

## Mô tả về trò chơi
Trò chơi được lấy cảm hứng bởi thể loại bắn súng, phiêu lưu. Ý tưởng chính là bạn được đặt vào một cốt truyện, trong cốt truyện đó bạn phải vượt qua quái vật, các mối hiểm họa để có thể tìm được phần thưởng ở cuối bản đồ.

## Các chức năng đã cài đặt
1. Menu đơn giản cho trò chơi
2. Xây dựng map gồm nhiều thành phần địa hình, vật trang trí
3. Cuốn chiếu map theo nhân vật di chuyển và xây dựng tương tác giữa nhân vật và map
4. Tạo ra hiệu ứng cho nhân vật di chuyển trái, phải, nhảy lên bằng ảnh nhiều frame
5. Nhân vật có thể đổi loại đạn
6. Tạo ra 2 loại quái vật: đứng im và chuyển động
7. Tạo ra boss cuối cùng
8. Tạo ra 2 loại đạn cho nhân vật
9. Xây dựng va chạm giữa nhân vật và quái, đạn với nhân vật, đạn với quái
10. Sử dụng font để hiển thị tiền, điểm đạt được, thời gian, ...
11. Tạo hiệu ứng âm thanh cho trò chơi: âm nền, âm thanh đạn bắn, âm thanh nhảy, âm thanh ăn tiền, âm thanh của boss, ...
-> Video minh họa: https://youtu.be/XDTeBPQfkfM 

## Các kỹ thuật lập trình được sử dụng
1. Mảng, vector
2. Con trỏ
3. Lớp, hướng đối tượng
4. Đồ họa (SDL2, SDL2_image)
5. Âm thanh (SDL2_mixer)
6. Đọc file và lưu trữ
7. Màn hình console (window.h)

## Kết luận
Đây là dòng game luôn luôn có thể phát triển theo hướng tuyến tính. Một vài hướng phát triển tiếp theo: xây dựng thêm map, thêm cốt truyện cho nhân vật, ...
### Những điều tâm đắc của em sau khi hoàn thành chương trình
-> Trải nghiệm quy trình phát triển sản phẩm thu nhỏ
-> Giúp em thực hành các kĩ thuật phát triển chương trình được dạy trên lớp: chia module, refractor, quy trình CDIO
-> Giúp em rèn thêm tính kiên nhẫn khi có bug
