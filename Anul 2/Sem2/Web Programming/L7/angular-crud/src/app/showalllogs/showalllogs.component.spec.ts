import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ShowalllogsComponent } from './showalllogs.component';

describe('ShowalllogsComponent', () => {
  let component: ShowalllogsComponent;
  let fixture: ComponentFixture<ShowalllogsComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ShowalllogsComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(ShowalllogsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
