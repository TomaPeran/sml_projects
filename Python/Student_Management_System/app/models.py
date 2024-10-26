from django.db import models
from django.contrib.auth.models import AbstractUser, Group
import random, string
# Create your models here.


class Role(models.Model):
    role = models.CharField(max_length=10, default="Student")

    def __str__(self):
        return self.role



class myUser(AbstractUser):
    STATUS_CHOICES = (
        ("None", "None"),
        ("Redovni", "Redovni"),
        ("Izvanredni", "Izvanredni"),
    )
    status = models.CharField(max_length=10, choices=STATUS_CHOICES, default="None")
    role = models.ForeignKey(Role, on_delete=models.CASCADE, null=False, blank=False)
    groups = models.ManyToManyField(Group, related_name='myUser_set', blank=True)
    username = None    
    email = models.EmailField('email address', unique=True)
    USERNAME_FIELD = 'email'
    REQUIRED_FIELDS = ['first_name', 'last_name', 'password', 'status', 'role']
    
    # Define user permissions field to avoid clashes with auth.User
    user_permissions = models.ManyToManyField(
        'auth.Permission',
        related_name='myUser_set',
        blank=True,
    )

    def __str__(self):
        return f'{self.first_name}, {self.last_name}, {self.email}'




class Subjects(models.Model):
    name = models.CharField(max_length=50)
    code = models.CharField(max_length=10)
    course = models.CharField(max_length=255)
    ects = models.IntegerField()
    semester = models.IntegerField()
    ELECTIVE_SUBJECT = (
        ("Yes", "Yes"),
        ("No", "No"),
    )
    elective = models.CharField(max_length=5, choices=ELECTIVE_SUBJECT, default="No") #Elective = izborni
    professor = models.ForeignKey(myUser, on_delete=models.CASCADE, null=True, blank=True) ## ovo cak i prominit u False, vidit/ rade cak i ne

    def __str__(self):
        return f'{self.name}'
    



class EnrollmentForm(models.Model):
    student_id = models.ForeignKey(myUser, on_delete=models.CASCADE, null=True, blank=True)
    subject_id = models.ForeignKey(Subjects, on_delete=models.CASCADE, null=True, blank=True)
    STATUS = (
        ("Neupisan", "Neupisan"),
        ("Upisan", "Upisan"),
        ("Polozen", "Polozen"),
        ("Izgubio potpis", "Izgubio potpis")
    )
    status = models.CharField(max_length=15, choices=STATUS, default="Neupisan")
    class Meta:
        unique_together = ('student_id', 'subject_id')

    def __str__(self):
        return f'{id}, ({self.student_id}, {self.subject_id}), {self.status}'