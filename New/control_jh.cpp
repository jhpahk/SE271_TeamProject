#include <iostream>

#include "control.h"

// Register
void Register::register_student(StudentDB* db) {
	int st_num;
	std::string pwd;
	std::cout << "�й��� �Է��� �ּ���: ";
	std::cin >> st_num;
	std::cout << std::endl;
	std::cout << "��й�ȣ�� �Է��� �ּ���: ";
	std::cin >> pwd;
	std::cout << std::endl;;
	Student student(st_num);
	student.set_password(pwd);
	db->add_student(&student);
	std::cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << std::endl;
}

void Register::register_admin(StudentDB* db) {
	std::string ad_id;
	std::string pwd;
	std::cout << "������ ID�� �Է��� �ּ���: ";
	std::cin >> ad_id;
	std::cout << std::endl;
	std::cout << "��й�ȣ�� �Է��� �ּ���: ";
	std::cin >> pwd;
	std::cout << std::endl;;
	Admin admin(ad_id);
	admin.set_password(pwd);
	db->add_admin(&admin);
	std::cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << std::endl;
}

// Log in
void LogIn::student_log_in(StudentDB* db, ControlByStudent* student) {
	int st_num;
	std::string pwd;
	Student* st;
	std::cout << "�й��� �Է��� �ּ���: ";
	std::cin >> st_num;
	std::cout << std::endl;
	st = db->get_student(st_num);
	if (st == nullptr) {
		std::cout << "��ϵ��� ���� �л��Դϴ�." << std::endl;
		return;
	}
	else {
		student->set_student(st);
	}
}
void LogIn::admin_log_in(StudentDB* db, ControlByAdmin* admin) {
	std::string adm_id;
	std::string pwd;
	Admin* adm;
	std::cout << "������ ID�� �Է��� �ּ���: ";
	std::cin >> adm_id;
	std::cout << std::endl;
	adm = db->get_admin(adm_id);
	if (adm == nullptr) {
		std::cout << "��ϵ��� ���� �������Դϴ�." << std::endl;
		return;
	}
	else {
		admin->set_admin(adm);
	}
}

// reservation, cancelation
void ControlByStudent::make_reservation(Seat* seat) {
	if (student->get_is_using()) {
		std::cout << "�̹� �������� �¼��� �ֽ��ϴ�." << std::endl;
		return;
	}
	if (seat->is_reserved()) {
		std::cout << "�̹� ����� �¼��Դϴ�." << std::endl;
		return;
	}
	student->set_is_using_reverse();
	student->set_seat_using(seat);

	seat->set_reservation_reverse();
	seat->set_res_student(student);
	seat->get_belong_to()->set_cur_using_num(seat->get_belong_to()->get_cur_using_num() + 1);
	std::cout << seat->get_seat_num() << "�� �¼� ����Ǿ����ϴ�." << std::endl;
}

void ControlByStudent::cancel_reservation() {
	if (!(student->get_is_using())) {
		std::cout << "�������� �¼��� �����ϴ�." << std::endl;
		return;
	}

	std::cout << student->get_seat_using()->get_seat_num() << "�� �¼� ������ ��ҵǾ����ϴ�." << std::endl;
	student->set_is_using_reverse();
	student->get_seat_using()->set_res_student(NULL);
	student->get_seat_using()->set_reservation_reverse();
	student->set_seat_using(NULL);
	student->get_seat_using()->get_belong_to()->set_cur_using_num(student->get_seat_using()->get_belong_to()->get_cur_using_num() - 1);
}

void ControlByStudent::report_away_from(Seat* seat) {			// ����� �׳� �Ű��ϸ� �ٷ� ���� ��ҵǵ��� ��. Ÿ�̸Ӹ� �־ ���� �ð� �ȿ� �ڸ��� ���ƿ��� �ڸ���� ����� �� �ֵ���!
	seat->set_away_from_reverse();
}

void ControlByStudent::cancel_away_from() {
	student->get_seat_using()->set_away_from_reverse();
}